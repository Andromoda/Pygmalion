//
// Created by vologhat on 19.12.2023.
//

#include "reflection.h"

jobject jni_reflection::get_app_class_loader(JNIEnv* env)
{
    jclass app_globals_clz=env->FindClass("android/app/AppGlobals");
    jmethodID get_init_app_mtd=env->GetStaticMethodID(app_globals_clz,"getInitialApplication","()Landroid/app/Application;");
    jobject app=env->CallStaticObjectMethod(app_globals_clz,get_init_app_mtd);

    jclass app_clz=env->FindClass("android/app/Application");
    jmethodID get_classloader_mtd=env->GetMethodID(app_clz,"getClassLoader","()Ljava/lang/ClassLoader;");

    return env->CallObjectMethod(app,get_classloader_mtd);
}

jclass jni_reflection::find_class(JNIEnv* env,const char* class_name)
{
    jobject classLoader=get_app_class_loader(env);
    jclass clz=env->GetObjectClass(classLoader);
    jmethodID loadClass=env->GetMethodID(clz,"loadClass","(Ljava/lang/String;)Ljava/lang/Class;");
    return static_cast< jclass >(env->CallObjectMethod(classLoader,loadClass,env->NewStringUTF(class_name)));
}