//
// Created by vologhat on 10/27/24.
//

#ifndef PYGMALION_HOOK_ASSETMAN_H
#define PYGMALION_HOOK_ASSETMAN_H

#include <jni.h>

typedef struct JNINativeMethodHook_t
{
    JNINativeMethod fn_info;
    void* fn_hook_ptr;
} jni_hook_t;

#define REGISTER_HOOK(SYMB,NAME,SIGN,RET_T,ARGS_T...) \
static RET_T hook_##SYMB(ARGS_T);                      \
static RET_T (*orig_##SYMB)(ARGS_T);                   \
static jni_hook_t g##SYMB                            \
{                                                      \
    {                                                  \
        NAME,                                          \
        SIGN,                                          \
        (void*)&orig_##SYMB /* hack to store original function address */ \
    },                                                 \
    (void*)hook_##SYMB                                \
};      \
RET_T hook_##SYMB(ARGS_T)

jint hook_assetman(JNIEnv* env,JNINativeMethod* gMethods,int numMethods);

#endif //PYGMALION_HOOK_ASSETMAN_H