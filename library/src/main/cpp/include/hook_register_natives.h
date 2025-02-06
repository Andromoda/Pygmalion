//
// Created by vologhat on 10/20/24.
//

#ifndef PYGMALION_HOOK_REGISTER_NATIVES_H
#define PYGMALION_HOOK_REGISTER_NATIVES_H

#include <jni.h>
#include <android/api-level.h>
#include <dlfcn.h>

#include "macros.h"
#include "sys_paths.h"
#include "dobby.h"

#include "AssetManagerHookFactory.h"

#define LIB_ANDROID_RUNTIME "libandroid_runtime.so"
#define LIB_ANDROID_RUNTIME_PATH SYSTEM_LIB_PATH LIB_ANDROID_RUNTIME
#define SIGN_REGISTER_ANDROID_CONTENT_ASSETMANAGER  "_ZN7android37register_android_content_AssetManagerEP7_JNIEnv"

/** initialization status indicator */
static bool gIsInitialized=false;

/** original methods */
static JNINativeMethod* gAssetManagerMethods=nullptr;
/** count of AssetManager JNI functions */
static int gNumAssetManagerMethods=0;

/** hook functions */
static JNINativeMethod* gHookAssetManagerMethods=nullptr;

jboolean jis_initialized(JNIEnv* env,jclass clz);
jboolean jhook(JNIEnv* env,jclass clz);
jboolean junhook(JNIEnv* env,jclass clz);

static const JNINativeMethod gMethods[]=
{
    { "isInitialized","()Z",reinterpret_cast< void* >(jis_initialized) },
    { "hook","()Z",reinterpret_cast< void* >(jhook) },
    { "unhook","()Z",reinterpret_cast< void* >(junhook) }
};

jint register_natives(JNIEnv* env);

#endif //PYGMALION_HOOK_REGISTER_NATIVES_H