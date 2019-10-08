//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_hue_filter.hpp"

ben::ngp::GPUImageHueFilter::GPUImageHueFilter(JNIEnv *env) : GPUImageFilter(NO_FILTER_VERTEX_SHADER, HUE_FRAGMENT_SHADER,env) {
    initialize(env);
    this->hue = 90.0f;
}

ben::ngp::GPUImageHueFilter::GPUImageHueFilter():GPUImageFilter(NO_FILTER_VERTEX_SHADER, HUE_FRAGMENT_SHADER) {
    this->hue = 90.0f;
}

void ben::ngp::GPUImageHueFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "hue", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getHue", kTypeFloat, NULL);
    cacheMethod(env, "setHue", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageHueFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("hue", kTypeFloat, &hue);
}

const char *ben::ngp::GPUImageHueFilter::getCanonicalName() const {
    return JAVA_HUE_FILTER;
}

void ben::ngp::GPUImageHueFilter::onInit() {
    GPUImageFilter::onInit();
    hueLocation = glGetUniformLocation(getGlProgId(), "hueAdjust");
}

void ben::ngp::GPUImageHueFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setHue(hue);
}

void ben::ngp::GPUImageHueFilter::setHue(float hue) {
    GPUImageHueFilter::hue = hue;
    float hueAdjust = ((int)this->hue % 360) * (float)3.14159265358979323846 / 180.0f;
    setFloat(hueLocation, hueAdjust);
}
