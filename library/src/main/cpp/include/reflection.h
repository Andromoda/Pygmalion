//
// Created by vologhat on 19.12.2023.
//

#ifndef REFLECTION_H
#define REFLECTION_H

#include <jni.h>

namespace jni_reflection
{
    jobject      get_app_class_loader(JNIEnv* env);
    jclass       find_class(JNIEnv* env,const char* class_name);
}

#endif //REFLECTION_H
