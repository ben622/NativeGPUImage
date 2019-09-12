//
// Created by ben622 on 2019/7/31.
//
#ifndef GPUIMAGE_MAIN_CPP
#define GPUIMAGE_MAIN_CPP

#include "include/jni/JniHelpers.h"

using namespace ben::jni;

ClassRegistry registry;

extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM *jvm, void *) {
    JNIEnv *env = jniHelpersInitialize(jvm);
    if (env == NULL) {
        return -1;
    }
    //register

    return JNI_VERSION_1_6;
}
#endif //GPUIMAGE_MAIN_CPP