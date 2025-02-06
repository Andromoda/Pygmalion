//
// Created by vologhat on 2/5/25.
//

#ifndef PYGMALION_HOOK_MACROS_H
#define PYGMALION_HOOK_MACROS_H

#include <android/api-level.h>
#include <type_traits>
#include "AssetManagerHookFactory.h"
#include "macros.h"

#define ASSET_MANAGER_HOOK(MIN_API,MAX_API,NAMESPACE,NAME,HOOK_IMPL_CLASS,TARGET_FUN_NAME,TARGET_FUN_SIGN,RET_T,...) \
static RET_T (*orig##NAMESPACE##NAME)(__VA_ARGS__);                                                                  \
static RET_T hook##NAMESPACE##NAME(__VA_ARGS__);                                                                     \
static AssetManagerHook gHook##NAMESPACE##NAME(                                                                      \
    {MIN_API,MAX_API},                                                                                               \
    HOOK_IMPL_CLASS,                                                                                                 \
    TARGET_FUN_NAME,                                                                                                 \
    TARGET_FUN_SIGN,                                                                                                 \
    (void*)hook##NAMESPACE##NAME,                                                                                    \
    (void**)&orig##NAMESPACE##NAME                                                                                   \
);                                                                                                                   \
RET_T hook##NAMESPACE##NAME(__VA_ARGS__)

static inline std::string stripOptimizeFlag(std::string sign)
{ return sign.substr(sign[0]=='!'); }

#define HOOK_BODY_VOID(NAMESPACE,NAME,env,clz,...) \
orig##NAMESPACE##NAME(env,clz,##__VA_ARGS__);      \
const auto& hook=gHook##NAMESPACE##NAME;           \
static jclass implClz=AssetManagerHookFactory::get().findClass(hook.mJavaImplClass); \
static jmethodID hookMtd=env->GetStaticMethodID(   \
        implClz,                                   \
        hook.mFunName.c_str(),                     \
        stripOptimizeFlag(hook.mFunSign).c_str()); \
env->CallStaticVoidMethod(implClz,hookMtd,##__VA_ARGS__)

#define HOOK_BODY_T(NAMESPACE,NAME,RET_T,EnvType,env,clz,...) \
const auto& res=orig##NAMESPACE##NAME(env,clz,##__VA_ARGS__); \
const auto& hook=gHook##NAMESPACE##NAME;                      \
static jclass implClz=AssetManagerHookFactory::get().findClass(hook.mJavaImplClass); \
static jmethodID hookMtd=env->GetStaticMethodID(              \
        implClz,                                              \
        hook.mFunName.c_str(),                                \
        stripOptimizeFlag(hook.mFunSign).c_str());            \
env->CallStatic##EnvType##Method(implClz,hookMtd,##__VA_ARGS__);                     \
return res

#define HOOK_BODY_BOOL(NAMESPACE,NAME,env,clz,...) HOOK_BODY_T(NAMESPACE,NAME,jboolean,Boolean,env,clz,##__VA_ARGS__)
#define HOOK_BODY_SHORT(NAMESPACE,NAME,env,clz,...) HOOK_BODY_T(NAMESPACE,NAME,jshort,Short,env,clz,##__VA_ARGS__)
#define HOOK_BODY_INT(NAMESPACE,NAME,env,clz,...) HOOK_BODY_T(NAMESPACE,NAME,jint,Int,env,clz,##__VA_ARGS__)
#define HOOK_BODY_LONG(NAMESPACE,NAME,env,clz,...) HOOK_BODY_T(NAMESPACE,NAME,jlong,Long,env,clz,##__VA_ARGS__)

#endif //PYGMALION_HOOK_MACROS_H
