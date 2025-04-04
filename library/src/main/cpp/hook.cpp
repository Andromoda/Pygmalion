//
// Created by vologhat on 10/20/24.
//

#include "hook.h"

static constexpr uint32_t kAccFastNative=0x00080000;//method (runtime; native only)
static constexpr uint32_t kAccNative    =0x0100;    //method

static std::vector< uint32_t*  > gAccessFlagMemmerAddresses;
static bool isFastNativeDisabled=false;

static inline int get_flags_member_offset();
static void grab_flag_member_addrs(JNIEnv* env, jclass asset_man_clz, JNINativeMethod* methods, int nmethods);
static bool re_register_assetmanager(JNIEnv* env, JNINativeMethod* gMethods, int numMethods);

install_hook_name(RegisterNativeMethods,jint,
                  JNIEnv* env,jclass clz,JNINativeMethod* gMethods,int nMethods)
{
    //backup original JNINativeMethod array
    gAssetManagerMethods=gMethods;
    gNumAssetManagerMethods=nMethods;

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

jint register_natives(JNIEnv* env)
{
    if(env->RegisterNatives(env->FindClass("com/vologhat/pygmalion/Pygmalion"),
                            gMethods,NELEM(gMethods)))
        return JNI_ERR;
    return JNI_OK;
}

void hook(JNIEnv* env)
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

jboolean jis_initialized(JNIEnv*,jclass)
{ return gIsInitialized; }

jboolean jhook(JNIEnv* env,jclass)
{
    return gIsInitialized
           &&re_register_assetmanager(env,gHookAssetManagerMethods,gNumAssetManagerMethods);
}

jboolean junhook(JNIEnv* env,jclass)
{
    return gIsInitialized
           &&re_register_assetmanager(env,gAssetManagerMethods,gNumAssetManagerMethods);
}

static inline bool need_disable_fastnative()
{
    return api_range {
        .min_api=__ANDROID_API_N__,
        .max_api=__ANDROID_API_N_MR1__
    }.isSupported(android_get_device_api_level());
}

static inline int get_flags_member_offset()
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

void grab_flag_member_addrs(JNIEnv* env,jclass asset_man_clz,JNINativeMethod* methods,int nmethods)
{
    for(auto i=0;i<nmethods;++i)
    {
        const auto& mtd=methods[i];
        const auto sign=strip_optimize_flag(mtd.signature);//strip optimize flag from JNI signature to resolve method id

        jmethodID jmtd=env->GetStaticMethodID(asset_man_clz,mtd.name,sign.c_str());
        if(env->ExceptionCheck())
        {
            env->ExceptionClear();
            jmtd=env->GetMethodID(asset_man_clz,mtd.name,sign.c_str());
        }

        const auto artMtdAddr=reinterpret_cast< ptrdiff_t >(jmtd);
        const auto flagMemAddr=reinterpret_cast< uint32_t* >(artMtdAddr +
                get_flags_member_offset());

        gAccessFlagMemmerAddresses.emplace_back(flagMemAddr);
    }
}

bool re_register_assetmanager(JNIEnv* env,JNINativeMethod* gMethods,int numMethods)
{
    const auto asset_man_clz=env->FindClass("android/content/res/AssetManager");

    if(need_disable_fastnative())
    {
        if(gAccessFlagMemmerAddresses.empty())
            grab_flag_member_addrs(env,asset_man_clz,gMethods,numMethods);
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