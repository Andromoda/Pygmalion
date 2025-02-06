//
// Created by vologhat on 19.12.2023.
//

#include "reflection.h"

jobject jni_reflection::get_app_class_loader(JNIEnv* env)
{
    auto app_globals_clz=env->FindClass("android/app/AppGlobals");
    auto get_init_app_mtd=env->GetStaticMethodID(app_globals_clz,"getInitialApplication","()Landroid/app/Application;");
    auto app=env->CallStaticObjectMethod(app_globals_clz,get_init_app_mtd);

    auto app_clz=env->FindClass("android/app/Application");
    auto get_classloader_mtd=env->GetMethodID(app_clz,"getClassLoader","()Ljava/lang/ClassLoader;");

    return env->CallObjectMethod(app,get_classloader_mtd);
}

jclass jni_reflection::find_class(JNIEnv* env,const char* class_name)
{
    auto classLoader=get_app_class_loader(env);
    auto clz=env->GetObjectClass(classLoader);
    auto loadClass=env->GetMethodID(clz,"loadClass","(Ljava/lang/String;)Ljava/lang/Class;");
    return reinterpret_cast< jclass >(env->CallObjectMethod(classLoader,loadClass,env->NewStringUTF(class_name)));
}