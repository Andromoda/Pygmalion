//
// Created by vologhat on 12/28/24.
//

#include "hook_macros.h"

static const std::string OREO_HOOK_IMPL_CLZ="com.vologhat.pygmalion.hooks.api.HookOreo";

ASSET_MANAGER_HOOK(__ANDROID_API_O__,__ANDROID_API_O_MR1__,
                   Oreo,LoadResourceValue,
                   OREO_HOOK_IMPL_CLZ,
                   "loadResourceValue","(ISLandroid/util/TypedValue;Z)I",
                   jint,
                   JNIEnv* env,jclass clz,
                   jint ident,
                   jshort density,
                   jobject outValue,
                   jboolean resolve)
{ HOOK_BODY_INT(Oreo,LoadResourceValue,env,clz,ident,density,outValue,resolve); }

ASSET_MANAGER_HOOK(__ANDROID_API_O__,__ANDROID_API_O_MR1__,
                   Oreo,LoadThemeAttributeValue,
                   OREO_HOOK_IMPL_CLZ,
                   "loadThemeAttributeValue","(JILandroid/util/TypedValue;Z)I",
                   jint,
                   JNIEnv* env,jclass clz,
                   jlong themeHandle,
                   jint ident,
                   jobject outValue,
                   jboolean resolve)
{ HOOK_BODY_INT(Oreo,LoadThemeAttributeValue,env,clz,themeHandle,ident,outValue,resolve); }

ASSET_MANAGER_HOOK(__ANDROID_API_O__,__ANDROID_API_O_MR1__,
                   Oreo,ApplyStyle,
                   OREO_HOOK_IMPL_CLZ,
                   "applyStyle","(JIIJ[IIJJ)V",
                   void,
                   JNIEnv* env,jclass clz,
                   jlong themeToken,
                   jint defStyleAttr,
                   jint defStyleRes,
                   jlong xmlParserToken,
                   jintArray attrsObj,
                   jint length,
                   jlong outValuesAddress,
                   jlong outIndicesAddress)
{ HOOK_BODY_VOID(Oreo,ApplyStyle,env,clz,themeToken,defStyleAttr,defStyleRes,xmlParserToken,attrsObj,length,outValuesAddress,outIndicesAddress); }

ASSET_MANAGER_HOOK(__ANDROID_API_O__,__ANDROID_API_O_MR1__,
                   Oreo,ResolveAttrs,
                   OREO_HOOK_IMPL_CLZ,
                   "resolveAttrs","(JII[I[I[I[I)Z",
                   jboolean,
                   JNIEnv* env,jclass clz,
                   jlong themeToken,
                   jint defStyleAttr,
                   jint defStyleRes,
                   jintArray inValues,
                   jintArray attrs,
                   jintArray outValues,
                   jintArray outIndices)
{ HOOK_BODY_BOOL(Oreo,ResolveAttrs,env,clz,themeToken,defStyleAttr,defStyleRes,inValues,attrs,outValues,outIndices); }

ASSET_MANAGER_HOOK(__ANDROID_API_O__,__ANDROID_API_O_MR1__,
                   Oreo,RetrieveAttributes,
                   OREO_HOOK_IMPL_CLZ,
                   "retrieveAttributes","(J[I[I[I)Z",
                   jboolean,
                   JNIEnv* env,jclass clz,
                   jlong xmlParserToken,
                   jintArray attrs,
                   jintArray outValues,
                   jintArray outIndices)
{ HOOK_BODY_BOOL(Oreo,RetrieveAttributes,env,clz,xmlParserToken,attrs,outValues,outIndices); }
