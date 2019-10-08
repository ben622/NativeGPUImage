//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_brightness_filter.hpp"

ben::ngp::GPUImageBrightnessFilter::GPUImageBrightnessFilter(JNIEnv *env) : GPUImageFilter(NO_FILTER_VERTEX_SHADER, BRIGHTNESS_FRAGMENT_SHADER,env) {
    initialize(env);
    this->brightness = 0.0f;
}

ben::ngp::GPUImageBrightnessFilter::GPUImageBrightnessFilter():GPUImageFilter(NO_FILTER_VERTEX_SHADER, BRIGHTNESS_FRAGMENT_SHADER) {
    this->brightness = 0.0f;
}

void ben::ngp::GPUImageBrightnessFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "brightness", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getBrightness", kTypeFloat, NULL);
    cacheMethod(env, "setBrightness", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageBrightnessFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("brightness", kTypeFloat, &brightness);
}

const char *ben::ngp::GPUImageBrightnessFilter::getCanonicalName() const {
    return JAVA_BRIGHTNESS_FILTER;
}

void ben::ngp::GPUImageBrightnessFilter::onInit() {
    GPUImageFilter::onInit();
    brightnessLocation = glGetUniformLocation(getGlProgId(), "brightness");
}

void ben::ngp::GPUImageBrightnessFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setBrightness(brightness);
}

void ben::ngp::GPUImageBrightnessFilter::setBrightness(float brightness) {
    GPUImageBrightnessFilter::brightness = brightness;
    setFloat(this->brightnessLocation, this->brightness);
}
