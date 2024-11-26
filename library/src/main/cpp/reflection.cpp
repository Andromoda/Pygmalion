//
// Created by vologhat on 19.12.2023.
//

#include "reflection.h"

jobject jni_reflection::get_app_class_loader(JNIEnv* env)
{
    jclass app_globals_clz=env->FindClass("android/app/AppGlobals");
    jmethodID get_init_app_mtd=env->GetStaticMethodID(app_globals_clz,"getInitialApplication","()Landroid/app/Application;");
    jobject app=env->CallStaticObjectMethod(app_globals_clz,get_init_app_mtd);

    jclass app_clz=env->FindClass("android/app/Application");
    jmethodID get_classloader_mtd=env->GetMethodID(app_clz,"getClassLoader","()Ljava/lang/ClassLoader;");

    return env->CallObjectMethod(app,get_classloader_mtd);
}

jclass jni_reflection::find_class(JNIEnv* env,const char* class_name)
{
    jobject classLoader=get_app_class_loader(env);
    jclass clz=env->GetObjectClass(classLoader);
    jmethodID loadClass=env->GetMethodID(clz,"loadClass","(Ljava/lang/String;)Ljava/lang/Class;");
    return static_cast< jclass >(env->CallObjectMethod(classLoader,loadClass,env->NewStringUTF(class_name)));
}

jclass jni_reflection::get_long_clz(JNIEnv* env)
{ return env->FindClass("java/lang/Long"); }

jclass jni_reflection::get_int_clz(JNIEnv* env)
{ return env->FindClass("java/lang/Integer"); }

jclass jni_reflection::get_short_clz(JNIEnv* env)
{ return env->FindClass("java/lang/Short"); }

jclass jni_reflection::get_double_clz(JNIEnv* env)
{ return env->FindClass("java/lang/Double"); }

jclass jni_reflection::get_float_clz(JNIEnv* env)
{ return env->FindClass("java/lang/Float"); }

jclass jni_reflection::get_char_clz(JNIEnv* env)
{ return env->FindClass("java/lang/Character"); }

jclass jni_reflection::get_bool_clz(JNIEnv* env)
{ return env->FindClass("java/lang/Boolean"); }

jclass jni_reflection::get_byte_clz(JNIEnv* env)
{ return env->FindClass("java/lang/Byte"); }

jclass jni_reflection::get_long_prim_clz(JNIEnv* env)
{
    jclass clz=get_long_clz(env);
    jfieldID type=env->GetStaticFieldID(clz,"TYPE","Ljava/lang/Class;");
    return static_cast< jclass >(env->GetStaticObjectField(clz,type));
}

jclass jni_reflection::get_int_prim_clz(JNIEnv* env)
{
    jclass clz=get_int_clz(env);
    jfieldID type=env->GetStaticFieldID(clz,"TYPE","Ljava/lang/Class;");
    return static_cast< jclass >(env->GetStaticObjectField(clz,type));
}

jclass jni_reflection::get_short_prim_clz(JNIEnv* env)
{
    jclass clz=get_short_clz(env);
    jfieldID type=env->GetStaticFieldID(clz,"TYPE","Ljava/lang/Class;");
    return static_cast< jclass >(env->GetStaticObjectField(clz,type));
}

jclass jni_reflection::get_double_prim_clz(JNIEnv* env)
{
    jclass clz=get_double_clz(env);
    jfieldID type=env->GetStaticFieldID(clz,"TYPE","Ljava/lang/Class;");
    return static_cast< jclass >(env->GetStaticObjectField(clz,type));
}

jclass jni_reflection::get_float_prim_clz(JNIEnv* env)
{
    jclass clz=get_float_clz(env);
    jfieldID type=env->GetStaticFieldID(clz,"TYPE","Ljava/lang/Class;");
    return static_cast< jclass >(env->GetStaticObjectField(clz,type));
}

jclass jni_reflection::get_char_prim_clz(JNIEnv* env)
{
    jclass clz=get_char_clz(env);
    jfieldID type=env->GetStaticFieldID(clz,"TYPE","Ljava/lang/Class;");
    return static_cast< jclass >(env->GetStaticObjectField(clz,type));
}

jclass jni_reflection::get_bool_prim_clz(JNIEnv* env)
{
    jclass clz=get_bool_clz(env);
    jfieldID type=env->GetStaticFieldID(clz,"TYPE","Ljava/lang/Class;");
    return static_cast< jclass >(env->GetStaticObjectField(clz,type));
}

jclass jni_reflection::get_byte_prim_clz(JNIEnv* env)
{
    jclass clz=get_byte_clz(env);
    jfieldID type=env->GetStaticFieldID(clz,"TYPE","Ljava/lang/Class;");
    return static_cast< jclass >(env->GetStaticObjectField(clz,type));
}

jobject jni_reflection::value_of(JNIEnv* env,jlong value)
{
    jclass clz=get_long_clz(env);
    jmethodID valueOf=env->GetStaticMethodID(clz,"valueOf","(J)Ljava/lang/Long;");
    return env->CallStaticObjectMethod(clz,valueOf,value);
}

jobject jni_reflection::value_of(JNIEnv* env,jint value)
{
    jclass clz=get_int_clz(env);
    jmethodID valueOf=env->GetStaticMethodID(clz,"valueOf","(I)Ljava/lang/Integer;");
    return env->CallStaticObjectMethod(clz,valueOf,value);
}

jobject jni_reflection::value_of(JNIEnv* env,jshort value)
{
    jclass clz=get_short_clz(env);
    jmethodID valueOf=env->GetStaticMethodID(clz,"valueOf","(S)Ljava/lang/Short;");
    return env->CallStaticObjectMethod(clz,valueOf,value);
}

jobject jni_reflection::value_of(JNIEnv* env,jdouble value)
{
    jclass clz=get_double_clz(env);
    jmethodID valueOf=env->GetStaticMethodID(clz,"valueOf","(D)Ljava/lang/Double;");
    return env->CallStaticObjectMethod(clz,valueOf,value);
}

jobject jni_reflection::value_of(JNIEnv* env,jfloat value)
{
    jclass clz=get_float_clz(env);
    jmethodID valueOf=env->GetStaticMethodID(clz,"valueOf","(F)Ljava/lang/Float;");
    return env->CallStaticObjectMethod(clz,valueOf,value);
}

jobject jni_reflection::value_of(JNIEnv* env,jchar value)
{
    jclass clz=get_float_clz(env);
    jmethodID valueOf=env->GetStaticMethodID(clz,"valueOf","(C)Ljava/lang/Float;");
    return env->CallStaticObjectMethod(clz,valueOf,value);
}

jobject jni_reflection::value_of(JNIEnv* env,jboolean value)
{
    jclass clz=get_bool_clz(env);
    jmethodID valueOf=env->GetStaticMethodID(clz,"valueOf","(Z)Ljava/lang/Boolean;");
    return env->CallStaticObjectMethod(clz,valueOf,value);
}

jobject jni_reflection::value_of(JNIEnv* env,jbyte value)
{
    jclass clz=get_bool_clz(env);
    jmethodID valueOf=env->GetStaticMethodID(clz,"valueOf","(B)Ljava/lang/Boolean;");
    return env->CallStaticObjectMethod(clz,valueOf,value);
}

jlong jni_reflection::long_value(JNIEnv* env,jobject value)
{
    jclass clz=env->GetObjectClass(value);
    jmethodID longValue=env->GetMethodID(clz,"longValue","()J");
    return env->CallLongMethod(value,longValue);
}

jint jni_reflection::int_value(JNIEnv* env,jobject value)
{
    jclass clz=env->GetObjectClass(value);
    jmethodID intValue=env->GetMethodID(clz,"intValue","()I");
    return env->CallIntMethod(value,intValue);
}

jshort jni_reflection::short_value(JNIEnv* env,jobject value)
{
    jclass clz=env->GetObjectClass(value);
    jmethodID shortValue=env->GetMethodID(clz,"shortValue","()S");
    return env->CallShortMethod(value,shortValue);
}

jdouble jni_reflection::double_value(JNIEnv* env,jobject value)
{
    jclass clz=env->GetObjectClass(value);
    jmethodID doubleValue=env->GetMethodID(clz,"doubleValue","()D");
    return env->CallDoubleMethod(value,doubleValue);
}

jfloat jni_reflection::float_value(JNIEnv* env,jobject value)
{
    jclass clz=env->GetObjectClass(value);
    jmethodID floatValue=env->GetMethodID(clz,"floatValue","()F");
    return env->CallFloatMethod(value,floatValue);
}

jchar jni_reflection::char_value(JNIEnv* env,jobject value)
{
    jclass clz=env->GetObjectClass(value);
    jmethodID charValue=env->GetMethodID(clz,"charValue","()C");
    return env->CallCharMethod(value,charValue);
}

jboolean jni_reflection::bool_value(JNIEnv* env,jobject value)
{
    jclass clz=env->GetObjectClass(value);
    jmethodID boolValue=env->GetMethodID(clz,"boolValue","()Z");
    return env->CallBooleanMethod(value,boolValue);
}

jbyte jni_reflection::byte_value(JNIEnv* env,jobject value)
{
    jclass clz=env->GetObjectClass(value);
    jmethodID boolValue=env->GetMethodID(clz,"byteValue","()Z");
    return env->CallBooleanMethod(value,boolValue);
}