//
// Created by vologhat on 10/20/24.
//

#include <jni_aux.h>
#include <dlfcn.h>

#include "macros.h"

#include "hooks/hook_register_natives.h"
#include "hooks/assetman/hook_assetman.h"

/** return the count of replaced JNI functions */
int8_t replace_ptrs(JNINativeMethod* methods,int nmethods,
                    jni_hook_t gMethodHooks[],int nhooks)
{
    int8_t replaced=0;

    //replace original functions with hooks
    for(auto i=0;i<nmethods;++i)
    {
        auto& target_mtd=methods[i];
        for(auto j=0;j<nhooks;++j)
        {
            auto& jni_hook=gMethodHooks[j];
            if(jni_hook.fn_info!=target_mtd)continue;
            LOGD("binding hook for function %s%s",target_mtd.name,target_mtd.signature);

            //reserve original function address to call it in hooks
            *static_cast< void** >(jni_hook.fn_info.fnPtr)=target_mtd.fnPtr;

            //reserve original function address to the hook struct for informational purposes
            jni_hook.fn_info.fnPtr=target_mtd.fnPtr;

            //replace original function address with hook function address
            target_mtd.fnPtr=jni_hook.fn_hook_ptr;

            ++replaced;
        }
    }

    return replaced;
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
    using RegisterAssetManager_t=int(*)(JNIEnv*);

    const auto register_natives_addr=reinterpret_cast< void* >(env->functions->RegisterNatives);

    //bind hook for RegisterNatives
    DobbyHook(register_natives_addr,
              reinterpret_cast< dobby_dummy_func_t >(fake_RegisterNativeMethods),
              reinterpret_cast< dobby_dummy_func_t* >(orig_RegisterNativeMethods));

    //trigger RegisterNatives for AssetManager to obtain data
    const auto register_asset_man=reinterpret_cast< RegisterAssetManager_t >(DobbySymbolResolver(LIB_ANDROID_RUNTIME_PATH,
                                                                                          SIGN_REGISTER_ANDROID_CONTENT_ASSETMANAGER));
    LOGD(SIGN_REGISTER_ANDROID_CONTENT_ASSETMANAGER" addr: %p",register_asset_man);
    register_asset_man(env);

    //unbind hook
    DobbyDestroy(register_natives_addr);

    gIsInitialized=gAssetManagerMethods&&gHookAssetManagerMethods
                   &&gNumAssetManagerMethods;
}

jint register_natives(JNIEnv* env)
{
    if(env->RegisterNatives(env->FindClass("com/vologhat/pygmalion/Pygmalion"),
                            gMethods,NELEM(gMethods)))
        return JNI_ERR;

    //we need to call it from JNI_OnLoad,
    //in other case it's crashed
    hook_RegisterNatives(env);

    return JNI_OK;
}

jboolean jis_initialized(JNIEnv*,jclass)
{ return gIsInitialized; }

jboolean jhook(JNIEnv* env,jclass)
{
    if(!gIsInitialized)return false;
    return hook_assetman(env,gHookAssetManagerMethods,gNumAssetManagerMethods);
}

jboolean junhook(JNIEnv* env,jclass)
{
    if(!gIsInitialized)return false;
    return hook_assetman(env,gAssetManagerMethods,gNumAssetManagerMethods);
}
