#include <jni.h>

#include "hook_register_natives.h"

extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM* vm,void* reserved)
{
    JNIEnv* env;
    if(vm->GetEnv(reinterpret_cast< void** >(&env),JNI_VERSION_1_6))
    {
        LOGE("JNI environment error");
        return JNI_ERR;
    }

    LOGD("Register JNI methods");
    if(register_natives(env))
    {
        LOGE("Failed to register JNI methods");
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}