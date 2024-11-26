//
// Created by vologhat on 19.12.2023.
//

#ifndef REFLECTION_H
#define REFLECTION_H

#include <jni.h>

namespace jni_reflection
{
    jobject      get_app_class_loader(JNIEnv* env);//for accessing application classes in the Android API level

    jclass       find_class(JNIEnv* env,const char* class_name);

    jclass       get_long_clz(JNIEnv* env);
    jclass       get_int_clz(JNIEnv* env);
    jclass       get_short_clz(JNIEnv* env);
    jclass       get_double_clz(JNIEnv* env);
    jclass       get_float_clz(JNIEnv* env);
    jclass       get_char_clz(JNIEnv* env);
    jclass       get_bool_clz(JNIEnv* env);
    jclass       get_byte_clz(JNIEnv* env);

    jclass       get_long_prim_clz(JNIEnv* env);
    jclass       get_int_prim_clz(JNIEnv* env);
    jclass       get_short_prim_clz(JNIEnv* env);
    jclass       get_double_prim_clz(JNIEnv* env);
    jclass       get_float_prim_clz(JNIEnv* env);
    jclass       get_char_prim_clz(JNIEnv* env);
    jclass       get_bool_prim_clz(JNIEnv* env);
    jclass       get_byte_prim_clz(JNIEnv* env);

    jobject      value_of(JNIEnv* env,jlong value);
    jobject      value_of(JNIEnv* env,jint value);
    jobject      value_of(JNIEnv* env,jshort value);
    jobject      value_of(JNIEnv* env,jdouble value);
    jobject      value_of(JNIEnv* env,jfloat value);
    jobject      value_of(JNIEnv* env,jchar value);
    jobject      value_of(JNIEnv* env,jboolean value);
    jobject      value_of(JNIEnv* env,jbyte value);

    jlong        long_value(JNIEnv* env,jobject value);
    jint         int_value(JNIEnv* env,jobject value);
    jshort       short_value(JNIEnv* env,jobject value);
    jdouble      double_value(JNIEnv* env,jobject value);
    jfloat       float_value(JNIEnv* env,jobject value);
    jchar        char_value(JNIEnv* env,jobject value);
    jboolean     bool_value(JNIEnv* env,jobject value);
    jbyte        byte_value(JNIEnv* env,jobject value);
}

#endif //REFLECTION_H
