//
// Created by ben622 on 2019/9/29.
//

#include "gpu_image_exposure_filter.hpp"

ben::ngp::GPUImageExposureFilter::GPUImageExposureFilter():GPUImageFilter(NO_FILTER_VERTEX_SHADER, EXPOSURE_FRAGMENT_SHADER) {
    this->exposure = 1.0f;
}

ben::ngp::GPUImageExposureFilter::GPUImageExposureFilter(JNIEnv *env) : GPUImageFilter(NO_FILTER_VERTEX_SHADER, EXPOSURE_FRAGMENT_SHADER,env) {
    initialize(env);
    this->exposure = 1.0f;
}

void ben::ngp::GPUImageExposureFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "exposure", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getExposure", kTypeFloat, NULL);
    cacheMethod(env, "setExposure", kTypeVoid, kTypeFloat, NULL);
    merge(this);

}

void ben::ngp::GPUImageExposureFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("exposure", kTypeFloat, &exposure);
}

const char *ben::ngp::GPUImageExposureFilter::getCanonicalName() const {
    return JAVA_EXPOSURE_FILTER;
}

void ben::ngp::GPUImageExposureFilter::onInit() {
    GPUImageFilter::onInit();
    exposureLocation = glGetUniformLocation(getGlProgId(), "exposure");
}

void ben::ngp::GPUImageExposureFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setExposure(exposure);
}

void ben::ngp::GPUImageExposureFilter::setExposure(float exposure) {
    GPUImageExposureFilter::exposure = exposure;
    setFloat(exposureLocation, this->exposure);
}
