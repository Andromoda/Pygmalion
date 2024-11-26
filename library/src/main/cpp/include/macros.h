//
// Created by vologhat on 10/19/24.
//

#ifndef PYGMALION_MACROS_H
#define PYGMALION_MACROS_H

#include <android/log.h>

#define NELEM(ARR) (sizeof(ARR)/sizeof(ARR[0]))

#define TAG "PygmalionNative"

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE,TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG,__VA_ARGS__)

#endif //PYGMALION_MACROS_H
