//
// Created by vologhat on 12/28/24.
//

#include "hook_macros.h"

static const std::string POSTOREO_HOOK_IMPL_CLZ="com.vologhat.pygmalion.hooks.api.HookPostOreo";

ASSET_MANAGER_HOOK(__ANDROID_API_P__,__ANDROID_API_FUTURE__,
                   PostOreo,LoadResourceValue,
                   POSTOREO_HOOK_IMPL_CLZ,
                   "nativeGetResourceValue","(JISLandroid/util/TypedValue;Z)I",
                   jint,
                   JNIEnv* env,jclass clz,
                   jlong ptr,
                   jint resid,
                   jshort density,
                   jobject typed_value,
                   jboolean resolve_references)
{ HOOK_BODY_INT(PostOreo,LoadResourceValue,env,clz,ptr,resid,density,typed_value,resolve_references); }

ASSET_MANAGER_HOOK(__ANDROID_API_P__,__ANDROID_API_FUTURE__,
                   PostOreo,LoadThemeAttributeValue,
                   POSTOREO_HOOK_IMPL_CLZ,
                   "nativeThemeGetAttributeValue","(JJILandroid/util/TypedValue;Z)I",
                   jint,
                   JNIEnv* env,jclass clz,
                   jlong ptr,
                   jlong theme_ptr,
                   jint resid,
                   jobject typed_value,
                   jboolean resolve_references)
{ HOOK_BODY_INT(PostOreo,LoadThemeAttributeValue,env,clz,ptr,theme_ptr,resid,typed_value,resolve_references); }

ASSET_MANAGER_HOOK(__ANDROID_API_P__,__ANDROID_API_FUTURE__,
                   PostOreo,ApplyStyle,
                   POSTOREO_HOOK_IMPL_CLZ,
                   "nativeApplyStyle","(JJIIJ[IJJ)V",
                   void,
                   JNIEnv* env,jclass clz,
                   jlong ptr,
                   jlong theme_ptr,
                   jint def_style_attr,
                   jint def_style_resid,
                   jlong xml_parser_ptr,
                   jintArray java_attrs,
                   jlong out_values_ptr,
                   jlong out_indices_ptr)
{ HOOK_BODY_VOID(PostOreo,ApplyStyle,env,clz,ptr,theme_ptr,def_style_attr,def_style_resid,xml_parser_ptr,java_attrs,out_values_ptr,out_indices_ptr); }

ASSET_MANAGER_HOOK(__ANDROID_API_P__,__ANDROID_API_FUTURE__,
                   PostOreo,ResolveAttrs,
                   POSTOREO_HOOK_IMPL_CLZ,
                   "nativeResolveAttrs","(JJII[I[I[I[I)Z",
                   jboolean,
                   JNIEnv* env,jclass clz,
                   jlong ptr,
                   jlong theme_ptr,
                   jint def_style_attr,
                   jint def_style_resid,
                   jintArray java_values,
                   jintArray java_attrs,
                   jintArray out_java_values,
                   jintArray out_java_indices)
{ HOOK_BODY_BOOL(PostOreo,ResolveAttrs,env,clz,ptr,theme_ptr,def_style_attr,def_style_resid,java_values,java_attrs,out_java_values,out_java_indices); }

ASSET_MANAGER_HOOK(__ANDROID_API_P__,__ANDROID_API_FUTURE__,
                   PostOreo,RetrieveAttributes,
                   POSTOREO_HOOK_IMPL_CLZ,
                   "nativeRetrieveAttributes","(JJ[I[I[I)Z",
                   jboolean,
                   JNIEnv* env,jclass clz,
                   jlong ptr,
                   jlong xml_parser_ptr,
                   jintArray java_attrs,
                   jintArray out_java_values,
                   jintArray out_java_indices)
{ HOOK_BODY_BOOL(PostOreo,RetrieveAttributes,env,clz,ptr,xml_parser_ptr,java_attrs,out_java_values,out_java_indices); }
