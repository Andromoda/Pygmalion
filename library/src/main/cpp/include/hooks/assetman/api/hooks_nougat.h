//
// Created by vologhat on 12/23/24.
//

#ifndef PYGMALION_HOOKS_NOUGAT_H
#define PYGMALION_HOOKS_NOUGAT_H

#include "hooks/assetman/hook_assetman.h"
#include "reflection.h"
#include "macros.h"

namespace hook_nougat
{
    static jclass getHookClz(JNIEnv* env)
    { return jni_reflection::find_class(env,"com.vologhat.pygmalion.hooks.api.HookNougat"); }

    HOOK(LoadResourceValue,"loadResourceValue","!(ISLandroid/util/TypedValue;Z)I",
         jint,
         jint ident,
         jshort density,
         jobject outValue,
         jboolean resolve)
    {
        HOOK_BODY_INT(LoadResourceValue,env,clazz,hook_nougat::getHookClz(env),ident,density,outValue,resolve);
    }

    HOOK(LoadThemeAttributeValue,"loadThemeAttributeValue","!(JILandroid/util/TypedValue;Z)I",
         jint,
         jlong themeHandle,
         jint ident,
         jobject outValue,
         jboolean resolve)
    {
        HOOK_BODY_INT(LoadThemeAttributeValue,env,clazz,hook_nougat::getHookClz(env),themeHandle,ident,outValue,resolve);
    }

    HOOK(ApplyStyle,"applyStyle","!(JIIJ[I[I[I)Z",
         jboolean,
         jlong themeToken,
         jint defStyleAttr,jint defStyleRes,
         jlong xmlParserToken,
         jintArray attrs,
         jintArray outValues,
         jintArray outIndices)
    {
        HOOK_BODY_BOOL(ApplyStyle,env,clazz,hook_nougat::getHookClz(env),themeToken,defStyleAttr,defStyleRes,xmlParserToken,attrs,outValues,outIndices);
    }

    HOOK(ResolveAttrs,"resolveAttrs","!(JII[I[I[I[I)Z",
         jboolean,
         jlong themeToken,
         jint defStyleAttr,
         jint defStyleRes,
         jintArray inValues,
         jintArray attrs,
         jintArray outValues,
         jintArray outIndices)
    {
        HOOK_BODY_BOOL(ResolveAttrs,env,clazz,hook_nougat::getHookClz(env),themeToken,defStyleAttr,defStyleRes,inValues,attrs,outValues,outIndices);
    }

    HOOK(RetrieveAttributes,"retrieveAttributes","!(J[I[I[I)Z",
         jboolean,
         jlong xmlParserToken,
         jintArray attrs,jintArray outValues,jintArray outIndices)
    {
        HOOK_BODY_BOOL(RetrieveAttributes,env,clazz,hook_nougat::getHookClz(env),xmlParserToken,attrs,outValues,outIndices);
    }
}

static jni_hook_t gHooksNougat[]=
{
    hook_nougat::gLoadResourceValue,
    hook_nougat::gLoadThemeAttributeValue,
    hook_nougat::gApplyStyle,
    hook_nougat::gResolveAttrs,
    hook_nougat::gRetrieveAttributes
};

#endif //PYGMALION_HOOKS_NOUGAT_H
