//
// Created by vologhat on 10/20/24.
//

#include "hook_register_natives.h"

static constexpr uint32_t kAccFastNative=0x00080000;//method (runtime; native only)
static constexpr uint32_t kAccNative    =0x0100;    //method

static std::vector< uint32_t*  > gAccessFlagMemmerAddresses;
static bool isFastNativeDisabled=false;

static inline int getFlagsMemberOffsetForApi();
static void grabFlagMemberAddresses(JNIEnv* env,jclass asset_man_clz,JNINativeMethod* methods,int nmethods);
static bool hook_assetman(JNIEnv* env,JNINativeMethod* gMethods,int numMethods);

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

    auto& factory=AssetManagerHookFactory::get();
    factory.init(env);

    const auto device_api=android_get_device_api_level();
    LOGD("Initialize Pygmalion for Api %d",device_api);

    const auto hooks=factory.getHooksForApi(device_api);
    if(hooks.empty())
    {
        LOGE("Hooks for api level %d not found",device_api);
        gIsInitialized=false;
        return 0;
    }

    const auto hooked=std::count_if(hooks.begin(),hooks.end(),[&](auto &hook) {
        for(auto i=0;i<gNumAssetManagerMethods;++i)
        {
            auto& jniMtd=gHookAssetManagerMethods[i];
            if(hook.mFunName==jniMtd.name
                &&hook.mFunSign==jniMtd.signature)
            {
                LOGD("Found hook for function %s%s on addr %p",jniMtd.name,jniMtd.signature,jniMtd.fnPtr);
                *hook.mOrigFunBackup=jniMtd.fnPtr;//backup original function address
                jniMtd.fnPtr=hook.mHookFunPtr;//replace original function address
                return true;
            }
        }
        return false;
    });

    gIsInitialized=hooks.size()==hooked;
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
    return gIsInitialized
        &&hook_assetman(env,gHookAssetManagerMethods,gNumAssetManagerMethods);
}

jboolean junhook(JNIEnv* env,jclass)
{
    return gIsInitialized
       &&hook_assetman(env,gAssetManagerMethods,gNumAssetManagerMethods);
}

static inline bool needDisableFastNative()
{
    return api_range {
        .min_api=__ANDROID_API_N__,
        .max_api=__ANDROID_API_N_MR1__
    }.isSupported(android_get_device_api_level());
}

static inline int getFlagsMemberOffsetForApi()
{
    const auto api_level=android_get_device_api_level();
    int mem_off=-1;
    //the issue with FastNative methods was found only on Android N,
    //so needs to deoptimize(remove FastNative flag from bitmask) only Android N hooks.
    //if the same issue will be found on other Android Apis, needs to deoptimize their hooks as well.
    switch(api_level)
    {
//        case __ANDROID_API_L__:
//            mem_off=56;
//            break;
//        case __ANDROID_API_L_MR1__:
//            mem_off=20;
//            break;
//        case __ANDROID_API_M__:
//            mem_off=12;
        case __ANDROID_API_N__:
        case __ANDROID_API_N_MR1__:
            mem_off=4;
            break;
    }
    return mem_off;
}

void grabFlagMemberAddresses(JNIEnv* env,jclass asset_man_clz,JNINativeMethod* methods,int nmethods)
{
    for(auto i=0;i<nmethods;++i)
    {
        const auto& mtd=methods[i];
        std::string sign;
        if(*mtd.signature=='!')
        {
            //remove optimize flag signature
            const auto len=strlen(mtd.signature+1);
            sign.resize(len);
            strncpy(sign.data(),mtd.signature+1,len);
        }
        else sign=std::string(mtd.signature);

        jmethodID jmtd=env->GetStaticMethodID(asset_man_clz, mtd.name, sign.c_str());
        if(env->ExceptionCheck())
        {
            env->ExceptionClear();
            jmtd=env->GetMethodID(asset_man_clz, mtd.name, sign.c_str());
        }

        const auto artMtdAddr=reinterpret_cast< ptrdiff_t >(jmtd);
        auto flagMemAddr=reinterpret_cast< uint32_t* >(artMtdAddr+getFlagsMemberOffsetForApi());

        gAccessFlagMemmerAddresses.emplace_back(flagMemAddr);
    }
}

bool hook_assetman(JNIEnv* env,JNINativeMethod* gMethods,int numMethods)
{
    const auto asset_man_clz=env->FindClass("android/content/res/AssetManager");

    if(needDisableFastNative())
    {
        if(gAccessFlagMemmerAddresses.empty())grabFlagMemberAddresses(env,asset_man_clz,gMethods,numMethods);
        if(!isFastNativeDisabled)
        {
            for(auto& addr:gAccessFlagMemmerAddresses)*addr&=~kAccFastNative;//clear FastNative flag
            isFastNativeDisabled=true;
        }
    }

    //just re-register native methods to hook
    env->UnregisterNatives(asset_man_clz);
    env->RegisterNatives(asset_man_clz,gMethods,numMethods);
    return true;
}