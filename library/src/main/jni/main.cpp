//
// Created by ben622 on 2019/7/31.
//
#ifndef GPUIMAGE_MAIN_CPP
#define GPUIMAGE_MAIN_CPP

#include "global_native_class_ptr.hpp"
#include "native_texture_image.cpp"
#include "gpu_image_render.hpp"

using namespace ben::jni;
extern ben::jni::ClassRegistry *classRegistryPtr;
extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM *jvm, void *) {
    JNIEnv *env = jniHelpersInitialize(jvm);
    if (env == NULL) {
        return -1;
    }
    //register
    classRegistryPtr->add(env, new ben::ngp::GPUImageRender(env));
    return JNI_VERSION_1_6;
}
#endif //GPUIMAGE_MAIN_CPP