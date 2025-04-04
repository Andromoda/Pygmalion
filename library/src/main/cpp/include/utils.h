//
// Created by vologhat on 19.12.2023.
//

#ifndef PYGMALION_UTILS_H
#define PYGMALION_UTILS_H

#include <jni.h>
#include <string>

std::string strip_optimize_flag(const std::string& sign);
jobject get_app_class_loader(JNIEnv* env);
jclass find_class(JNIEnv* env,const std::string& class_name);

#endif //PYGMALION_UTILS_H
