//
// Created by vologhat on 19.12.2023.
//

#include "utils.h"

std::string strip_optimize_flag(const std::string& sign)
{ return sign.substr(sign[0]=='!'); }

jobject get_app_class_loader(JNIEnv* env)
{
    auto app_globals_clz=env->FindClass("android/app/AppGlobals");
    auto get_init_app_mtd=env->GetStaticMethodID(app_globals_clz,"getInitialApplication","()Landroid/app/Application;");
    auto app=env->CallStaticObjectMethod(app_globals_clz,get_init_app_mtd);

    auto app_clz=env->FindClass("android/app/Application");
    auto get_classloader_mtd=env->GetMethodID(app_clz,"getClassLoader","()Ljava/lang/ClassLoader;");

    return env->CallObjectMethod(app,get_classloader_mtd);
}

jclass find_class(JNIEnv* env,const std::string& class_name)
{
    static auto classLoader=get_app_class_loader(env);
    static auto clz=env->GetObjectClass(classLoader);
    static auto loadClass=env->GetMethodID(clz,"loadClass","(Ljava/lang/String;)Ljava/lang/Class;");
    return reinterpret_cast< jclass >(env->CallObjectMethod(classLoader,loadClass,env->NewStringUTF(class_name.c_str())));
}