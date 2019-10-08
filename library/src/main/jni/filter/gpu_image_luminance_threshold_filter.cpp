//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_luminance_threshold_filter.hpp"

ben::ngp::GPUImageLuminanceThresholdFilter::GPUImageLuminanceThresholdFilter():GPUImageFilter(NO_FILTER_VERTEX_SHADER, LUMINANCE_THRESHOLD_FRAGMENT_SHADER) {}

ben::ngp::GPUImageLuminanceThresholdFilter::GPUImageLuminanceThresholdFilter(JNIEnv *env)
        : GPUImageFilter(NO_FILTER_VERTEX_SHADER, LUMINANCE_THRESHOLD_FRAGMENT_SHADER,env) {
    initialize(env);
}

void ben::ngp::GPUImageLuminanceThresholdFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "threshold", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getThreshold", kTypeFloat, NULL);
    cacheMethod(env, "setThreshold", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageLuminanceThresholdFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("threshold", kTypeFloat, &threshold);
}

const char *ben::ngp::GPUImageLuminanceThresholdFilter::getCanonicalName() const {
    return JAVA_LUMINANCE_THRESHOLD_FILTER;
}

void ben::ngp::GPUImageLuminanceThresholdFilter::onInit() {
    GPUImageFilter::onInit();
    uniformThresholdLocation = glGetUniformLocation(getGlProgId(), "threshold");
}

void ben::ngp::GPUImageLuminanceThresholdFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setThreshold(threshold);
}

void ben::ngp::GPUImageLuminanceThresholdFilter::setThreshold(float threshold) {
    GPUImageLuminanceThresholdFilter::threshold = threshold;
    setFloat(uniformThresholdLocation, threshold);
}
