//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_sobel_threshold_filter.hpp"

ben::ngp::GPUImageSobelThresholdFilter::GPUImageSobelThresholdFilter():GPUImage3x3TextureSamplingFilter(SOBEL_THRESHOLD_EDGE_DETECTION) {
    this->threshold = 0.9f;
}

ben::ngp::GPUImageSobelThresholdFilter::GPUImageSobelThresholdFilter(JNIEnv *env)
        : GPUImage3x3TextureSamplingFilter(env,SOBEL_THRESHOLD_EDGE_DETECTION) {
    initialize(env);
    this->threshold = 0.9f;
}

void ben::ngp::GPUImageSobelThresholdFilter::initialize(JNIEnv *env) {
    GPUImage3x3TextureSamplingFilter::initialize(env);
    cacheField(env, "threshold", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getThreshold", kTypeFloat, NULL);
    cacheMethod(env, "setThreshold", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageSobelThresholdFilter::mapFields() {
    GPUImage3x3TextureSamplingFilter::mapFields();
    mapField("threshold", kTypeFloat, &threshold);
}

const char *ben::ngp::GPUImageSobelThresholdFilter::getCanonicalName() const {
    return JAVA_SOBEL_THRESHOLD_FILTER;
}

void ben::ngp::GPUImageSobelThresholdFilter::onInit() {
    GPUImage3x3TextureSamplingFilter::onInit();
    uniformThresholdLocation = glGetUniformLocation(getGlProgId(), "threshold");

}

void ben::ngp::GPUImageSobelThresholdFilter::onInitialized() {
    GPUImage3x3TextureSamplingFilter::onInitialized();
    setThreshold(threshold);
}

void ben::ngp::GPUImageSobelThresholdFilter::setThreshold(float threshold) {
    GPUImageSobelThresholdFilter::threshold = threshold;
    setFloat(uniformThresholdLocation, threshold);
}
