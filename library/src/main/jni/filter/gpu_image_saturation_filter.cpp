//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_saturation_filter.hpp"


ben::ngp::GPUImageSaturationFilter::GPUImageSaturationFilter() : GPUImageFilter(
        NO_FILTER_VERTEX_SHADER, SATURATION_FRAGMENT_SHADER) {
    this->saturation = 1.0f;
}

ben::ngp::GPUImageSaturationFilter::GPUImageSaturationFilter(JNIEnv *env) : GPUImageFilter(
        NO_FILTER_VERTEX_SHADER, SATURATION_FRAGMENT_SHADER, env) {
    initialize(env);
    this->saturation = 1.0f;
}

void ben::ngp::GPUImageSaturationFilter::onInit() {
    GPUImageFilter::onInit();
    saturationLocation = glGetUniformLocation(getGlProgId(), "saturation");
}

void ben::ngp::GPUImageSaturationFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setSaturation(saturation);
}


void ben::ngp::GPUImageSaturationFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "saturation", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getSaturation", kTypeFloat, NULL);
    cacheMethod(env, "setSaturation", kTypeVoid, kTypeFloat, NULL);
    merge(this);

}

void ben::ngp::GPUImageSaturationFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("saturation", kTypeFloat, &saturation);
}

const char *ben::ngp::GPUImageSaturationFilter::getCanonicalName() const {
    return JAVA_SATURATION_FILTER;
}

void ben::ngp::GPUImageSaturationFilter::setSaturation(float saturation) {
    GPUImageSaturationFilter::saturation = saturation;
    setFloat(saturationLocation, this->saturation);
}

