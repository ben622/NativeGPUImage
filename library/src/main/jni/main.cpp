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
    classRegistryPtr->add(env, new GPUImage3x3TextureSamplingFilter(env));
    classRegistryPtr->add(env, new GPUImageWeakPixelInclusionFilter(env));
    classRegistryPtr->add(env, new GPUImageVignetteFilter(env));
    classRegistryPtr->add(env, new GPUImageVibranceFilter(env));
    classRegistryPtr->add(env, new GPUImageAddBlendFilter(env));
    classRegistryPtr->add(env, new GPUImageToonFilter(env));
    classRegistryPtr->add(env, new GPUImageGammaFilter(env));
    classRegistryPtr->add(env, new GPUImageFalseColorFilter(env));
    classRegistryPtr->add(env, new GPUImageExposureFilter(env));
    classRegistryPtr->add(env, new GPUImageExclusionBlendFilter(env));
    classRegistryPtr->add(env, new GPUImage3x3ConvolutionFilter(env));
    classRegistryPtr->add(env, new GPUImageEmbossFilter(env));
    classRegistryPtr->add(env, new GPUImageDivideBlendFilter(env));
    classRegistryPtr->add(env, new GPUImageAlphaBlendFilter(env));
    classRegistryPtr->add(env, new GPUImageDissolveBlendFilter(env));
    classRegistryPtr->add(env, new GPUImageGrayscaleFilter(env));
    classRegistryPtr->add(env, new GPUImageSobelEdgeDetectionFilter(env));
    classRegistryPtr->add(env, new GPUImageSaturationFilter(env));
    classRegistryPtr->add(env, new GPUImageContrastFilter(env));
    classRegistryPtr->add(env, new GPUImageBrightnessFilter(env));
    classRegistryPtr->add(env, new GPUImageLevelsFilter(env));
    classRegistryPtr->add(env, new GPUImageRGBFilter(env));
    classRegistryPtr->add(env, new GPUImageRGBDilationFilter(env));
    classRegistryPtr->add(env, new GPUImageHueFilter(env));
    classRegistryPtr->add(env, new GPUImageMonochromeFilter(env));
    classRegistryPtr->add(env, new GPUImageSharpenFilter(env));
    classRegistryPtr->add(env, new GPUImageHighlightShadowFilter(env));
    classRegistryPtr->add(env, new GPUImageHazeFilter(env));
    //register android gl bridge.
    classRegistryPtr->add(env, new NativeFilter(env));
    classRegistryPtr->add(env, new NGPNativeBridge(env));
    //register render.
    classRegistryPtr->add(env, new GPUImageRender(env));

    return JNI_VERSION_1_6;
}
#endif //GPUIMAGE_MAIN_CPP