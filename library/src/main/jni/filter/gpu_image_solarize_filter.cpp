//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_solarize_filter.hpp"

ben::ngp::GPUImageSolarizeFilter::GPUImageSolarizeFilter():GPUImageFilter(NO_FILTER_VERTEX_SHADER, SOLATIZE_FRAGMENT_SHADER) {}

ben::ngp::GPUImageSolarizeFilter::GPUImageSolarizeFilter(JNIEnv *env) : GPUImageFilter(NO_FILTER_VERTEX_SHADER, SOLATIZE_FRAGMENT_SHADER,env) {
    initialize(env);
}

void ben::ngp::GPUImageSolarizeFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "threshold", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getThreshold", kTypeFloat, NULL);
    cacheMethod(env, "setThreshold", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageSolarizeFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("threshold", kTypeFloat, &threshold);
}

const char *ben::ngp::GPUImageSolarizeFilter::getCanonicalName() const {
    return JAVA_SOLARIZE_FILTER;
}

void ben::ngp::GPUImageSolarizeFilter::onInit() {
    GPUImageFilter::onInit();
    uniformThresholdLocation = glGetUniformLocation(getGlProgId(), "threshold");
}

void ben::ngp::GPUImageSolarizeFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setThreshold(threshold);
}

void ben::ngp::GPUImageSolarizeFilter::setThreshold(float threshold) {
    GPUImageSolarizeFilter::threshold = threshold;
    setFloat(uniformThresholdLocation, threshold);
}
