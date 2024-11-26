//
// Created by vologhat on 10/20/24.
//

#include <string>
#include <dlfcn.h>

#include "hooks/hook_register_natives.h"
#include "hooks/assetman/hook_assetman.h"

#include "macros.h"

static inline bool operator==(const JNINativeMethod& a,const JNINativeMethod& b)
{
    return !strcmp(a.name,b.name)
           &&!strcmp(a.signature,b.signature);//for possible overloading
}

bool replace_ptrs(JNINativeMethod* methods,int nmethods,
                  jni_hook_t gMethodHooks[],int nhooks)
{
    int8_t hooked=0;

    //replace original functions with hooks
    for(auto i=0;i<nmethods;++i)
    {
        auto& target_mtd=methods[i];
        for(auto j=0;j<nhooks;++j)
        {
            const auto& jni_hook=gMethodHooks[j];
            if(jni_hook.fn_info==target_mtd)
            {
                LOGD("binding hook for function %s%s",target_mtd.name,target_mtd.signature);

                //backup original function address
                *static_cast< void** >(jni_hook.fn_info.fnPtr)=target_mtd.fnPtr;
                target_mtd.fnPtr=jni_hook.fn_hook_ptr;

                ++hooked;
            }
        }
    }

    return hooked==nhooks;
}

install_hook_name(RegisterNativeMethods,jint,
                  JNIEnv* env,jclass clz,JNINativeMethod* gMethods,int nMethods)
{
    //obtain data
    gAssetManagerMethods=gMethods;
    gNumAssetManagerMethods=nMethods;

    //don't need to free dynamic memory here
    //it will be freed during exiting
    gHookAssetManagerMethods=new JNINativeMethod[nMethods];
    memcpy(gHookAssetManagerMethods,gMethods,sizeof(JNINativeMethod)*nMethods);

    replace_ptrs(gHookAssetManagerMethods,nMethods,gHooksPostOreo,NELEM(gHooksPostOreo));

    return 0;
}

void hook_RegisterNatives(JNIEnv* env)
{
    //get address of RegisterNatives function
    const auto addr=reinterpret_cast< void* >(env->functions->RegisterNatives);

    //bind hook for RegisterNatives
    DobbyHook(addr,
              reinterpret_cast< dobby_dummy_func_t >(fake_RegisterNativeMethods),
              reinterpret_cast< dobby_dummy_func_t* >(orig_RegisterNativeMethods));

    //trigger RegisterNatives for AssetManager to obtain data
    const auto register_asset_man=reinterpret_cast< int(*)(JNIEnv*) >(DobbySymbolResolver(LIB_ANDROID_RUNTIME_PATH,
                                                                                          SIGN_REGISTER_ANDROID_CONTENT_ASSETMANAGER));
    LOGD(SIGN_REGISTER_ANDROID_CONTENT_ASSETMANAGER" addr: %p",register_asset_man);

    register_asset_man(env);

    //unbind hook
    DobbyDestroy(addr);

    gIsInitialized=gAssetManagerMethods&&gHookAssetManagerMethods
                   &&gNumAssetManagerMethods;
}

jint register_natives(JNIEnv* env)
{
    if(env->RegisterNatives(env->FindClass("com/vologhat/pygmalion/Pygmalion"),
                                gMethods,NELEM(gMethods)))
        return JNI_ERR;

    hook_RegisterNatives(env);

    return JNI_OK;
}

jboolean jis_initialized(JNIEnv*,jclass)
{ return gIsInitialized; }

jboolean jhook(JNIEnv* env,jclass)
{
    if(gIsInitialized)return hook_assetman(env,gHookAssetManagerMethods,gNumAssetManagerMethods);
    return false;
}

jboolean junhook(JNIEnv* env,jclass)
{
    if(gIsInitialized)return hook_assetman(env,gAssetManagerMethods,gNumAssetManagerMethods);
    return false;
}
