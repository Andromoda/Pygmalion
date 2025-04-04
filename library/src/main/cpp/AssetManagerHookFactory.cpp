//
// Created by vologhat on 1/4/25.
//

#include "AssetManagerHookFactory.h"

AssetManagerHookFactory AssetManagerHookFactory::sInstance;

std::vector< AssetManagerHook > AssetManagerHookFactory::getHooksForApi(api_level api)
{
   for(const auto& [api_range,hooks]:mHookMap)
   {
       if(api_range.isSupported(api))return hooks;
   }
   return {};
}

void AssetManagerHookFactory::registerHook(api_range range,const AssetManagerHook& hook)
{ mHookMap[range].emplace_back(hook); }

void AssetManagerHookFactory::init(JNIEnv* env)
{
    for(const auto& [_,hooks]:mHookMap)
    {
        const auto& hookImplClassName=hooks.front().mJavaImplClass;
        auto clz=find_class(env,hookImplClassName);
        clz=(jclass)env->NewGlobalRef(clz);
        mHookImplClassMap[hookImplClassName]=clz;
    }
}

jclass AssetManagerHookFactory::findClass(const std::string& className)
{ return mHookImplClassMap[className]; }

