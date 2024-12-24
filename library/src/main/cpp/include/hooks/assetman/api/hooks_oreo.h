//
// Created by vologhat on 12/23/24.
//

#ifndef PYGMALION_HOOKS_OREO_H
#define PYGMALION_HOOKS_OREO_H

#include <string>

#include "hooks/assetman/hook_assetman.h"
#include "reflection.h"
#include "macros.h"

namespace hook_oreo
{
    static jclass getHookClz(JNIEnv* env)
    { return jni_reflection::find_class(env,"com.vologhat.pygmalion.hooks.api.HookOreo"); }

    HOOK(LoadResourceValue,"loadResourceValue","!(ISLandroid/util/TypedValue;Z)I",
         jint,
         jint ident,
         jshort density,
         jobject outValue,
         jboolean resolve)
    {
        HOOK_BODY_INT(LoadResourceValue,env,clazz,hook_oreo::getHookClz(env),ident,density,outValue,resolve);
    }

    HOOK(LoadThemeAttributeValue,"loadThemeAttributeValue","!(JILandroid/util/TypedValue;Z)I",
         jint,
         jlong themeHandle,
         jint ident,
         jobject outValue,
         jboolean resolve)
    {
        HOOK_BODY_INT(LoadThemeAttributeValue,env,clazz,hook_oreo::getHookClz(env),themeHandle,ident,outValue,resolve);
    }

    HOOK(ApplyStyle,"applyStyle","!(JIIJ[IIJJ)Z",
         void,
         jlong themeToken,
         jint defStyleAttr,jint defStyleRes,
         jlong xmlParserToken,
         jintArray attrsObj,
         jint length,
         jlong outValuesAddress,jlong outIndicesAddress)
    {
        HOOK_BODY_VOID(ApplyStyle,env,clazz,hook_oreo::getHookClz(env),themeToken,defStyleAttr,defStyleRes,xmlParserToken,attrsObj,length,outValuesAddress,outIndicesAddress);
    }

    HOOK(ResolveAttrs,"resolveAttrs","(JII[I[I[I[I)Z",
         jboolean,
         jlong themeToken,
         jint defStyleRes,
         jintArray inValues,jintArray attrs,jintArray outValues,jintArray outIndices)
    {
        HOOK_BODY_BOOL(ResolveAttrs,env,clazz,hook_oreo::getHookClz(env),themeToken,defStyleRes,inValues,attrs,outValues,outIndices);
    }

    HOOK(RetrieveAttributes,"retrieveAttributes","(J[I[I[I)Z",
         jboolean,
         jlong xmlParserToken,
         jintArray attrs,jintArray outValues,jintArray outIndices)
    {
        HOOK_BODY_BOOL(RetrieveAttributes,env,clazz,hook_oreo::getHookClz(env),xmlParserToken,attrs,outValues,outIndices);
    }
}

static jni_hook_t gHooksOreo[]=
{
    hook_oreo::gLoadResourceValue,
    hook_oreo::gLoadThemeAttributeValue,
    hook_oreo::gApplyStyle,
    hook_oreo::gResolveAttrs,
    hook_oreo::gRetrieveAttributes
};

#endif //PYGMALION_HOOKS_OREO_H
