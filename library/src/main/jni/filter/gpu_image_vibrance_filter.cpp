//
// Created by ben622 on 2019/9/28.
//

#include "gpu_image_vibrance_filter.hpp"

ben::ngp::GPUImageVibranceFilter::GPUImageVibranceFilter():GPUImageFilter(NO_FILTER_VERTEX_SHADER, VIBRANCE_FRAGMENT_SHADER) {
    this->vibrance = 0.0f;
}

ben::ngp::GPUImageVibranceFilter::GPUImageVibranceFilter(JNIEnv *env) : GPUImageFilter(NO_FILTER_VERTEX_SHADER, VIBRANCE_FRAGMENT_SHADER,env) {
    initialize(env);
    this->vibrance = 0.0f;

}
void ben::ngp::GPUImageVibranceFilter::onInit() {
    GPUImageFilter::onInit();
    vibranceLocation = glGetUniformLocation(getGlProgId(), "vibrance");
}

void ben::ngp::GPUImageVibranceFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setVibrance(vibrance);
}


void ben::ngp::GPUImageVibranceFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "vibrance", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getVibrance", kTypeFloat, NULL);
    cacheMethod(env, "setVibrance", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageVibranceFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("vibrance", kTypeFloat, &vibrance);
}

const char *ben::ngp::GPUImageVibranceFilter::getCanonicalName() const {
    return JAVA_VIBRANCE_FILTER;
}

void ben::ngp::GPUImageVibranceFilter::setVibrance(float vibrance) {
    GPUImageVibranceFilter::vibrance = vibrance;
    if (isInitialized()) {
        setFloat(vibranceLocation, vibrance);
    }
}

