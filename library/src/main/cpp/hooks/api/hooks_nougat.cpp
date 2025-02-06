//
// Created by vologhat on 12/28/24.
//

#include "hook_macros.h"

static const std::string NOUGAT_HOOK_IMPL_CLZ="com.vologhat.pygmalion.hooks.api.HookNougat";

ASSET_MANAGER_HOOK(__ANDROID_API_N__,__ANDROID_API_N_MR1__,
                   Nougat,LoadResourceValue,
                   NOUGAT_HOOK_IMPL_CLZ,
                   "loadResourceValue","!(ISLandroid/util/TypedValue;Z)I",
                   jint,
                   JNIEnv* env,jclass clz,
                   jint ident,
                   jshort density,
                   jobject outValue,
                   jboolean resolve)
{ HOOK_BODY_INT(Nougat,LoadResourceValue,env,clz,ident,density,outValue,resolve); }

ASSET_MANAGER_HOOK(__ANDROID_API_N__,__ANDROID_API_N_MR1__,
                   Nougat,LoadThemeAttributeValue,
                   NOUGAT_HOOK_IMPL_CLZ,
                   "loadThemeAttributeValue","!(JILandroid/util/TypedValue;Z)I",
                   jint,
                   JNIEnv* env,jclass clz,
                   jlong themeHandle,
                   jint ident,
                   jobject outValue,
                   jboolean resolve)
{ HOOK_BODY_INT(Nougat,LoadThemeAttributeValue,env,clz,themeHandle,ident,outValue,resolve); }

ASSET_MANAGER_HOOK(__ANDROID_API_N__,__ANDROID_API_N_MR1__,
                   Nougat,ApplyStyle,
                   NOUGAT_HOOK_IMPL_CLZ,
                   "applyStyle","!(JIIJ[I[I[I)Z",
                   jboolean,
                   JNIEnv* env,jclass clz,
                   jlong themeToken,
                   jint defStyleAttr,jint defStyleRes,
                   jlong xmlParserToken,
                   jintArray attrs,
                   jintArray outValues,
                   jintArray outIndices)
{ HOOK_BODY_BOOL(Nougat,ApplyStyle,env,clz,themeToken,defStyleAttr,defStyleRes,xmlParserToken,attrs,outValues,outIndices); }

ASSET_MANAGER_HOOK(__ANDROID_API_N__,__ANDROID_API_N_MR1__,
                   Nougat,ResolveAttrs,
                   NOUGAT_HOOK_IMPL_CLZ,
                   "resolveAttrs","!(JII[I[I[I[I)Z",
                   jboolean,
                   JNIEnv* env,jclass clz,
                   jlong themeToken,
                   jint defStyleAttr,
                   jint defStyleRes,
                   jintArray inValues,
                   jintArray attrs,
                   jintArray outValues,
                   jintArray outIndices)
{ HOOK_BODY_BOOL(Nougat,ResolveAttrs,env,clz,themeToken,defStyleAttr,defStyleRes,inValues,attrs,outValues,outIndices); }

ASSET_MANAGER_HOOK(__ANDROID_API_N__,__ANDROID_API_N_MR1__,
                   Nougat,RetrieveAttributes,
                   NOUGAT_HOOK_IMPL_CLZ,
                   "retrieveAttributes","!(J[I[I[I)Z",
                   jboolean,
                   JNIEnv* env,jclass clz,
                   jlong xmlParserToken,
                   jintArray attrs,
                   jintArray outValues,
                   jintArray outIndices)
{ HOOK_BODY_BOOL(Nougat,RetrieveAttributes,env,clz,xmlParserToken,attrs,outValues,outIndices); }
