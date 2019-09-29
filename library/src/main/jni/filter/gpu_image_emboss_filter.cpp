//
// Created by ben622 on 2019/9/29.
//

#include "gpu_image_emboss_filter.hpp"
#include "../include/jni/JniHelpersCommon.h"

ben::ngp::GPUImageEmbossFilter::GPUImageEmbossFilter() {
    this->intensity = 1.0f;
}

ben::ngp::GPUImageEmbossFilter::GPUImageEmbossFilter(JNIEnv *env) : GPUImage3x3ConvolutionFilter(
        env) {
    initialize(env);
    this->intensity = 1.0f;
}

void ben::ngp::GPUImageEmbossFilter::initialize(JNIEnv *env) {
    GPUImage3x3ConvolutionFilter::initialize(env);
    cacheField(env, "intensity", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getIntensity", kTypeFloat, NULL);
    cacheMethod(env, "setIntensity", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageEmbossFilter::mapFields() {
    GPUImage3x3ConvolutionFilter::mapFields();
    mapField("intensity", kTypeFloat, &intensity);
}

const char *ben::ngp::GPUImageEmbossFilter::getCanonicalName() const {
    return JAVA_EMBOSS_FILTER;
}

void ben::ngp::GPUImageEmbossFilter::onInit() {
    GPUImage3x3ConvolutionFilter::onInit();
}

void ben::ngp::GPUImageEmbossFilter::onInitialized() {
    GPUImage3x3ConvolutionFilter::onInitialized();
    setIntensity(intensity);
}

void ben::ngp::GPUImageEmbossFilter::setIntensity(float intensity) {
    GPUImageEmbossFilter::intensity = intensity;
    setConvolutionKernel(new float[9]{
            intensity * (-2.0f), -intensity, 0.0f,
            -intensity, 1.0f, intensity,
            0.0f, intensity, intensity * 2.0f,
    });
}
