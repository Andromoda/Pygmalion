//
// Created by vologhat on 1/4/25.
//

#ifndef PYGMALION_ASSETMANAGERHOOKFACTORY_H
#define PYGMALION_ASSETMANAGERHOOKFACTORY_H

#include <map>
#include <set>
#include <string>
#include <jni.h>
#include "reflection.h"

typedef uint32_t api_level;

struct api_range;
class AssetManagerHook;
class AssetManagerHookFactory;

struct api_range
{
    const api_level min_api,max_api;

    inline bool isSupported(const api_level api) const
    { return api>=min_api&&api<=max_api; }

    inline bool operator<(const api_range& other) const
    { return max_api<other.min_api; }
};

class AssetManagerHookFactory
{
private:
    static AssetManagerHookFactory sInstance;
    std::map< api_range,std::vector< AssetManagerHook > > mHookMap;
    std::map< std::string,jclass > mHookImplClassMap;
private:
    AssetManagerHookFactory()=default;
    AssetManagerHookFactory(const AssetManagerHookFactory&)=default;
    ~AssetManagerHookFactory()=default;
public:
    static AssetManagerHookFactory& get()
    { return sInstance; }

    void init(JNIEnv* env);

    jclass findClass(const std::string& className);

    void registerHook(api_range range,const AssetManagerHook& hook);

    std::vector< AssetManagerHook > getHooksForApi(api_level api);
};

class AssetManagerHook
{
public:
    api_range mSupportedApis;
    std::string mJavaImplClass,mFunName,mFunSign;
    void* mHookFunPtr;
    void** mOrigFunBackup;
public:
    AssetManagerHook()=delete;
    AssetManagerHook(const AssetManagerHook&)=default;
    ~AssetManagerHook()=default;
public:
    AssetManagerHook(
            api_range supportedApis,
            std::string javaClass,
            std::string functionName,
            std::string functionSignature,
            void* hookFunctionPtr,
            void** origFunBackup
    ):mSupportedApis(supportedApis),
      mJavaImplClass(std::move(javaClass)),
      mFunName(std::move(functionName)),
      mFunSign(std::move(functionSignature)),
      mHookFunPtr(hookFunctionPtr),
      mOrigFunBackup(origFunBackup)
    {
        AssetManagerHookFactory::get().registerHook(supportedApis,*this);
    }

    inline bool isSupported(const api_level api) const
    { return mSupportedApis.isSupported(api); }
};

#endif //PYGMALION_ASSETMANAGERHOOKFACTORY_H
