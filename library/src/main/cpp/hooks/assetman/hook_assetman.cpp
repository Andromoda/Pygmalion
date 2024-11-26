//
// Created by vologhat on 10/27/24.
//

#include <android/api-level.h>
#include <string>

#include "hooks/assetman/api/hooks_postoreo.h"
#include "hooks/assetman/hook_assetman.h"
#include "macros.h"

jint hook_assetman(JNIEnv* env,JNINativeMethod* gMethods,int numMethods)
{
    //just re-register native methods to hook
    const auto asset_man_clz=env->FindClass("android/content/res/AssetManager");
    return !env->UnregisterNatives(asset_man_clz)
           &&!env->RegisterNatives(asset_man_clz,gMethods,numMethods);
}