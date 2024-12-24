//
// Created by vologhat on 10/27/24.
//

#include <android/api-level.h>
#include <string>

#include "hooks/assetman/api/hooks_postoreo.h"
#include "hooks/assetman/hook_assetman.h"
#include "macros.h"

typedef uint32_t* mem_ptr;

static constexpr uint32_t kAccFastNative=0x00080000;//method (runtime; native only)
static constexpr uint32_t kAccNative    =0x0100;    //method

std::vector< mem_ptr > gAccessFlagMemmerAddrs;
bool isFastNativeDisabled=false;

void deopt_mtds(JNIEnv* env,jclass asset_man_clz,JNINativeMethod* methods,int nmethods,int mem_off)
{
    for(auto i=0;i<nmethods;++i)
    {
        const auto& mtd=methods[i];
        std::string sign;
        if(*mtd.signature=='!')
        {
            //remove optimize flag from the JNI function signature
            const auto len=strlen(mtd.signature+1);
            sign.resize(len);
            strncpy(sign.data(),mtd.signature+1,len);
        }
        else sign=std::string(mtd.signature);

        //all native methods in the AssetManager are static
        jmethodID mtd_id=env->GetStaticMethodID(asset_man_clz,mtd.name,sign.c_str());
        if(env->ExceptionCheck())
        {
            env->ExceptionClear();
            mtd_id=env->GetMethodID(asset_man_clz,mtd.name,sign.c_str());
        }

        const auto art_mtd=reinterpret_cast< char* >(mtd_id);
        auto flags_addr=reinterpret_cast< uint32_t* >(art_mtd+mem_off);

        gAccessFlagMemmerAddrs.emplace_back(flags_addr);
    }
}

bool hook_assetman(JNIEnv* env,JNINativeMethod* gMethods,int numMethods)
{
    const auto asset_man_clz=env->FindClass("android/content/res/AssetManager");

    const auto api_level=android_get_device_api_level();
    if(api_level>=__ANDROID_API_N__&&api_level<__ANDROID_API_O__)
    {
        int mem_off;
        switch(api_level)
        {
            case __ANDROID_API_L__:
                mem_off=56;
                break;
            case __ANDROID_API_L_MR1__:
                mem_off=20;
                break;
            case __ANDROID_API_M__:
                mem_off=12;
            case __ANDROID_API_N__:
            case __ANDROID_API_N_MR1__:
                mem_off=4;
                break;
            default:
                return false;
        }

        if(gAccessFlagMemmerAddrs.empty())
            deopt_mtds(env,asset_man_clz,gMethods,numMethods,mem_off);

        //clear FastNative flag
        if(!isFastNativeDisabled)
        {
            for(auto& addr:gAccessFlagMemmerAddrs)*addr&=~kAccFastNative;
            isFastNativeDisabled=true;
        }
    }

    //just re-register native methods to hook
    return !env->UnregisterNatives(asset_man_clz)
           &&!env->RegisterNatives(asset_man_clz,gMethods,numMethods);
}