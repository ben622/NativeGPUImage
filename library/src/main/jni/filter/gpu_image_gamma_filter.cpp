//
// Created by ben622 on 2019/9/29.
//

#include "gpu_image_gamma_filter.hpp"

ben::ngp::GPUImageGammaFilter::GPUImageGammaFilter():GPUImageFilter(NO_FILTER_VERTEX_SHADER, GAMMA_FRAGMENT_SHADER) {
    this->gamma = 1.2f;
}

ben::ngp::GPUImageGammaFilter::GPUImageGammaFilter(JNIEnv *env) : GPUImageFilter(NO_FILTER_VERTEX_SHADER, GAMMA_FRAGMENT_SHADER,env) {

    initialize(env);
    this->gamma = 1.2f;

}

void ben::ngp::GPUImageGammaFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "gamma", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getGamma", kTypeFloat, NULL);
    cacheMethod(env, "setGamma", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageGammaFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("gamma", kTypeFloat, &gamma);
}

const char *ben::ngp::GPUImageGammaFilter::getCanonicalName() const {
    return JAVA_GAMMA_FILTER;
}

void ben::ngp::GPUImageGammaFilter::setGamma(float gamma) {
    GPUImageGammaFilter::gamma = gamma;
    setFloat(gammaLocation, this->gamma);
}

void ben::ngp::GPUImageGammaFilter::onInit() {
    GPUImageFilter::onInit();
    gammaLocation = glGetUniformLocation(getGlProgId(), "gamma");
}

void ben::ngp::GPUImageGammaFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setGamma(gamma);
}
