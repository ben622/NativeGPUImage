//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_contrast_filter.hpp"

ben::ngp::GPUImageContrastFilter::GPUImageContrastFilter(): GPUImageFilter(NO_FILTER_VERTEX_SHADER, CONTRAST_FRAGMENT_SHADER) {
    this->contrast = 1.2f;
}

ben::ngp::GPUImageContrastFilter::GPUImageContrastFilter(JNIEnv *env) : GPUImageFilter(NO_FILTER_VERTEX_SHADER, CONTRAST_FRAGMENT_SHADER,env) {
    initialize(env);
    this->contrast = 1.2f;
}

void ben::ngp::GPUImageContrastFilter::setContrast(float contrast) {
    GPUImageContrastFilter::contrast = contrast;
    setFloat(contrastLocation, this->contrast);
}

void ben::ngp::GPUImageContrastFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "contrast", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getContrast", kTypeFloat, NULL);
    cacheMethod(env, "setContrast", kTypeVoid, kTypeFloat, NULL);
    merge(this);

}

void ben::ngp::GPUImageContrastFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("contrast", kTypeFloat, &contrast);
}

const char *ben::ngp::GPUImageContrastFilter::getCanonicalName() const {
    return JAVA_CONTRAST_FILTER;
}

void ben::ngp::GPUImageContrastFilter::onInit() {
    GPUImageFilter::onInit();
    contrastLocation = glGetUniformLocation(getGlProgId(), "contrast");
}

void ben::ngp::GPUImageContrastFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setContrast(contrast);
}


