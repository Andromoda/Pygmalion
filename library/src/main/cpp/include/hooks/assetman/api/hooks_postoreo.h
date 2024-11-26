//
// Created by vologhat on 10/27/24.
//

#ifndef PYGMALION_HOOKS_POSTOREO_H
#define PYGMALION_HOOKS_POSTOREO_H

#include <string>

#include "hooks/assetman/hook_assetman.h"
#include "reflection.h"
#include "macros.h"

namespace hook_post_oreo
{
    static jclass getHookClz(JNIEnv* env)
    { return jni_reflection::find_class(env,"com.vologhat.pygmalion.hooks.api.HookPostOreo"); }

    REGISTER_HOOK(NativeGetResourceValue,"nativeGetResourceValue","(JISLandroid/util/TypedValue;Z)I",
                  jint,
                  JNIEnv* env,jclass clazz,
                  jlong ptr,
                  jint resid,
                  jshort density,
                  jobject typed_value,
                  jboolean resolve_references)
    {
        jint cookie=orig_NativeGetResourceValue(env,clazz,ptr,resid,density,typed_value,resolve_references);

        jclass clz=hook_post_oreo::getHookClz(env);
        const auto& fn_info=gNativeGetResourceValue.fn_info;
        jmethodID mtd=env->GetStaticMethodID(clz,fn_info.name,fn_info.signature);
        env->CallStaticIntMethod(clz,mtd,ptr,resid,density,typed_value,resolve_references);

        return cookie;
    }

    REGISTER_HOOK(NativeThemeGetAttributeValue,"nativeThemeGetAttributeValue","(JJILandroid/util/TypedValue;Z)I",
                  jint,
                  JNIEnv* env,jclass clazz,
                  jlong ptr,jlong theme_ptr,
                  jint resid,
                  jobject typed_value,
                  jboolean resolve_references)
    {
        jint cookie=orig_NativeThemeGetAttributeValue(env,clazz,ptr,theme_ptr,resid,typed_value,resolve_references);

        jclass clz=hook_post_oreo::getHookClz(env);
        const auto& fn_info=gNativeThemeGetAttributeValue.fn_info;
        jmethodID mtd=env->GetStaticMethodID(clz,fn_info.name,fn_info.signature);
        env->CallStaticIntMethod(clz,mtd,ptr,theme_ptr,resid,typed_value,resolve_references);

        return cookie;
    }

    REGISTER_HOOK(NativeApplyStyle,"nativeApplyStyle","(JJIIJ[IJJ)V",
                  void,
                  JNIEnv* env,jclass clazz,
                  jlong ptr,jlong theme_ptr,
                  jint def_style_attr,jint def_style_resid,jlong xml_parser_ptr,
                  jintArray java_attrs,jlong out_values_ptr,jlong out_indices_ptr)
    {
        orig_NativeApplyStyle(env,clazz,ptr,theme_ptr,def_style_attr,def_style_resid,xml_parser_ptr,java_attrs,out_values_ptr,out_indices_ptr);

        jclass clz=hook_post_oreo::getHookClz(env);
        const auto& fn_info=gNativeApplyStyle.fn_info;
        jmethodID mtd=env->GetStaticMethodID(clz,fn_info.name,fn_info.signature);
        env->CallStaticVoidMethod(clz,mtd,ptr,theme_ptr,def_style_attr,def_style_resid,xml_parser_ptr,java_attrs,out_values_ptr,out_indices_ptr);
    }

    REGISTER_HOOK(NativeResolveAttrs,"nativeResolveAttrs","(JJII[I[I[I[I)Z",
                  jboolean,
                  JNIEnv* env,jclass clazz,
                  jlong ptr,jlong theme_ptr,
                  jint def_style_attr,jint def_style_resid,
                  jintArray java_values,jintArray java_attrs,jintArray out_java_values,jintArray out_java_indices)
    {
        jboolean res=orig_NativeResolveAttrs(env,clazz,ptr,theme_ptr,def_style_attr,def_style_resid,java_values,java_attrs,out_java_values,out_java_indices);

        jclass clz=hook_post_oreo::getHookClz(env);
        const auto& fn_info=gNativeResolveAttrs.fn_info;
        jmethodID mtd=env->GetStaticMethodID(clz,fn_info.name,fn_info.signature);
        env->CallStaticBooleanMethod(clz,mtd,ptr,theme_ptr,def_style_attr,def_style_resid,java_values,java_attrs,out_java_values,out_java_indices);

        return res;
    }

    REGISTER_HOOK(NativeRetrieveAttributes,"nativeRetrieveAttributes","(JJ[I[I[I)Z",
                  jboolean,
                  JNIEnv* env,jclass clazz,
                  jlong ptr,jlong xml_parser_ptr,
                  jintArray java_attrs,jintArray out_java_values,jintArray out_java_indices)
    {
        jboolean res=orig_NativeRetrieveAttributes(env,clazz,ptr,xml_parser_ptr,java_attrs,out_java_values,out_java_indices);

        jclass clz=hook_post_oreo::getHookClz(env);
        const auto& fn_info=gNativeRetrieveAttributes.fn_info;
        jmethodID mtd=env->GetStaticMethodID(clz,fn_info.name,fn_info.signature);
        env->CallStaticBooleanMethod(clz,mtd,ptr,xml_parser_ptr,java_attrs,out_java_values,out_java_indices);

        return res;
    }
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
