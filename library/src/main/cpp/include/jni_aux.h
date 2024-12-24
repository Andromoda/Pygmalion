//
// Created by vologhat on 11/30/24.
//

#ifndef PYGMALION_JNI_AUX_H
#define PYGMALION_JNI_AUX_H

#include <jni.h>
#include <string>

static inline bool operator!=(const JNINativeMethod& a,const JNINativeMethod& b)
{
    return std::string(a.name)!=std::string(b.name)
           ||std::string(a.signature)!=std::string(b.signature);
}

static inline bool operator==(const JNINativeMethod& a,const JNINativeMethod& b)
{
    return std::string(a.name)==std::string(b.name)
           &&std::string(a.signature)==std::string(b.signature);
}

#endif //PYGMALION_JNI_AUX_H
