//
// Created by ben622 on 2019/7/31.
//
#ifndef GPUIMAGE_MAIN_CPP
#define GPUIMAGE_MAIN_CPP

#include "gpu_image_render.hpp"
#include "api/android_gl_bridge.hpp"
#include "api/android_native_filter.hpp"

using namespace ben::jni;
using namespace ben::ngp;

extern ben::jni::ClassRegistry *classRegistryPtr;

extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM *jvm, void *) {
    JNIEnv *env = jniHelpersInitialize(jvm);
    if (env == NULL) {
        return -1;
    }

    //register native filter.
    classRegistryPtr->add(env, new GPUImageGaussianBlurFilter(env));
    classRegistryPtr->add(env, new GPUImageDilationFilter(env));
    classRegistryPtr->add(env, new GPUImagePixelationFilter(env));
    classRegistryPtr->add(env, new GPUImageZoomBlurFilter(env));
    classRegistryPtr->add(env, new GPUImageWhiteBalanceFilter(env));
    //register android gl bridge.
    classRegistryPtr->add(env, new NativeFilter(env));
    classRegistryPtr->add(env, new NGPNativeBridge(env));
    //register render.
    classRegistryPtr->add(env, new GPUImageRender(env));

    return JNI_VERSION_1_6;
}
#endif //GPUIMAGE_MAIN_CPP