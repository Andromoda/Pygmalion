//
// Created by vologhat on 10/27/24.
//

#ifndef PYGMALION_HOOK_ASSETMAN_H
#define PYGMALION_HOOK_ASSETMAN_H

#include <jni.h>
#include <type_traits>
#include <functional>

typedef struct JNINativeMethodHook_t
{
    JNINativeMethod fn_info;
    void* fn_hook_ptr;
} jni_hook_t;

#define HOOK_BODY_VOID(symb,env,clz,hook_clz,...) \
orig_##symb(env,clz,##__VA_ARGS__); \
const auto& hook_fn_info=g##symb.fn_info; \
static jmethodID mtd=env->GetStaticMethodID(hook_clz,hook_fn_info.name,hook_fn_info.signature); \
env->CallStaticVoidMethod(hook_clz,mtd,##__VA_ARGS__);

#define HOOK_BODY_T(symb,ret_t,fun_suffix,env,clz,hook_clz,...) \
const auto& res=orig_##symb(env,clz,##__VA_ARGS__);              \
\
const auto& hook_fn_info=g##symb.fn_info;                                                                \
static jmethodID mtd=env->GetStaticMethodID(hook_clz,hook_fn_info.name,hook_fn_info.signature); \
env->CallStatic##fun_suffix##Method(hook_clz,mtd,##__VA_ARGS__); \
                                                                \
return res

#define HOOK_BODY_BOOL(symb,env,clz,hook_clz,...) HOOK_BODY_T(symb,jboolean,Boolean,env,clz,hook_clz,##__VA_ARGS__)
#define HOOK_BODY_SHORT(symb,env,clz,hook_clz,...) HOOK_BODY_T(symb,jshort,Short,env,clz,hook_clz,##__VA_ARGS__)
#define HOOK_BODY_INT(symb,env,clz,hook_clz,...) HOOK_BODY_T(symb,jint,Int,env,clz,hook_clz,##__VA_ARGS__)
#define HOOK_BODY_LONG(symb,env,clz,hook_clz,...) HOOK_BODY_T(symb,jlong,Long,env,clz,hook_clz,##__VA_ARGS__)

#define HOOK(symb,func_name,func_sign,ret_t,args_t...) \
static ret_t hook_##symb(JNIEnv* env,jclass clazz,##args_t);                      \
static ret_t (*orig_##symb)(JNIEnv* env,jclass clazz,##args_t);                   \
static jni_hook_t g##symb                            \
{                                                      \
    {                                                  \
        func_name,                                          \
        func_sign,                                          \
        (void*)&orig_##symb /*store address of backup symbol to initialize it later. */ \
    },                                                 \
    (void*)hook_##symb                                \
};                                   \
ret_t hook_##symb(JNIEnv* env,jclass clazz,##args_t)

jint hook_assetman(JNIEnv* env,JNINativeMethod* gMethods,int numMethods);

#endif //PYGMALION_HOOK_ASSETMAN_H