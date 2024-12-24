//
// Created by vologhat on 10/27/24.
//

#ifndef PYGMALION_HOOKS_POSTOREO_H
#define PYGMALION_HOOKS_POSTOREO_H

#include "hooks/assetman/hook_assetman.h"
#include "reflection.h"
#include "macros.h"

namespace hook_post_oreo
{
    static jclass getHookClz(JNIEnv* env)
    { return jni_reflection::find_class(env,"com.vologhat.pygmalion.hooks.api.HookPostOreo"); }

    HOOK(NativeGetResourceValue,"nativeGetResourceValue","(JISLandroid/util/TypedValue;Z)I",
         jint,
         jlong ptr,
         jint resid,
         jshort density,
         jobject typed_value,
         jboolean resolve_references
     )
    { HOOK_BODY_INT(NativeGetResourceValue,env,clazz,hook_post_oreo::getHookClz(env),ptr,resid,density,typed_value,resolve_references); }

    HOOK(NativeThemeGetAttributeValue,"nativeThemeGetAttributeValue","(JJILandroid/util/TypedValue;Z)I",
         jint,
         jlong ptr,jlong theme_ptr,
         jint resid,
         jobject typed_value,
         jboolean resolve_references
    )
    { HOOK_BODY_INT(NativeThemeGetAttributeValue,env,clazz,hook_post_oreo::getHookClz(env),ptr,theme_ptr,resid,typed_value,resolve_references); }

    HOOK(NativeApplyStyle,"nativeApplyStyle","(JJIIJ[IJJ)V",
         void,
         jlong ptr,jlong theme_ptr,
         jint def_style_attr,jint def_style_resid,jlong xml_parser_ptr,
         jintArray java_attrs,jlong out_values_ptr,jlong out_indices_ptr
    )
    { HOOK_BODY_VOID(NativeApplyStyle,env,clazz,hook_post_oreo::getHookClz(env),ptr,theme_ptr,def_style_attr,def_style_resid,xml_parser_ptr,java_attrs,out_values_ptr,out_indices_ptr); }

    HOOK(NativeResolveAttrs,"nativeResolveAttrs","(JJII[I[I[I[I)Z",
         jboolean,
         jlong ptr,jlong theme_ptr,
         jint def_style_attr,jint def_style_resid,
         jintArray java_values,jintArray java_attrs,jintArray out_java_values,jintArray out_java_indices
    )
    { HOOK_BODY_BOOL(NativeResolveAttrs,env,clazz,hook_post_oreo::getHookClz(env),ptr,theme_ptr,def_style_attr,def_style_resid,java_values,java_attrs,out_java_values,out_java_indices); }

    HOOK(NativeRetrieveAttributes,"nativeRetrieveAttributes","(JJ[I[I[I)Z",
         jboolean,
         jlong ptr,jlong xml_parser_ptr,
         jintArray java_attrs,jintArray out_java_values,jintArray out_java_indices
    )
    { HOOK_BODY_BOOL(NativeRetrieveAttributes,env,clazz,hook_post_oreo::getHookClz(env),ptr,xml_parser_ptr,java_attrs,out_java_values,out_java_indices); }
}

static jni_hook_t gHooksPostOreo[]=
{
    hook_post_oreo::gNativeGetResourceValue,
    hook_post_oreo::gNativeThemeGetAttributeValue,
    hook_post_oreo::gNativeApplyStyle,
    hook_post_oreo::gNativeResolveAttrs,
    hook_post_oreo::gNativeRetrieveAttributes,
};

#endif //PYGMALION_HOOKS_POSTOREO_H
