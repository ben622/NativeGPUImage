//
// Created by ben622 on 2019/9/29.
//

#include "gpu_image_toon_filter.hpp"

ben::ngp::GPUImageToonFilter::GPUImageToonFilter() :GPUImage3x3TextureSamplingFilter(TOON_FRAGMENT_SHADER){
    this->threshold = 0.2f;
    this->quantizationLevels = 10.0f;
}

ben::ngp::GPUImageToonFilter::GPUImageToonFilter(JNIEnv *env) : GPUImage3x3TextureSamplingFilter(
        env,TOON_FRAGMENT_SHADER) {
    initialize(env);
    this->threshold = 0.2f;
    this->quantizationLevels = 10.0f;
}

void ben::ngp::GPUImageToonFilter::initialize(JNIEnv *env) {
    GPUImage3x3TextureSamplingFilter::initialize(env);
    cacheField(env, "threshold", kTypeFloat);
    cacheField(env, "quantizationLevels", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getThreshold", kTypeFloat, NULL);
    cacheMethod(env, "setThreshold", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getQuantizationLevels", kTypeFloat, NULL);
    cacheMethod(env, "setQuantizationLevels", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageToonFilter::mapFields() {
    GPUImage3x3TextureSamplingFilter::mapFields();
    mapField("threshold", kTypeFloat, &threshold);
    mapField("quantizationLevels", kTypeFloat, &quantizationLevels);
}

const char *ben::ngp::GPUImageToonFilter::getCanonicalName() const {
    return JAVA_TOON_FILTER;
}

void ben::ngp::GPUImageToonFilter::onInit() {
    GPUImage3x3TextureSamplingFilter::onInit();
    thresholdLocation = glGetUniformLocation(getGlProgId(), "threshold");
    quantizationLevelsLocation = glGetUniformLocation(getGlProgId(), "quantizationLevels");
}

void ben::ngp::GPUImageToonFilter::onInitialized() {
    GPUImage3x3TextureSamplingFilter::onInitialized();
    setThreshold(threshold);
    setQuantizationLevels(quantizationLevels);
}

void ben::ngp::GPUImageToonFilter::setThreshold(float threshold) {
    GPUImageToonFilter::threshold = threshold;
    setFloat(thresholdLocation, threshold);
}

void ben::ngp::GPUImageToonFilter::setQuantizationLevels(float quantizationLevels) {
    GPUImageToonFilter::quantizationLevels = quantizationLevels;
    setFloat(quantizationLevelsLocation, quantizationLevels);
}
