//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_sharpen_filter.hpp"

ben::ngp::GPUImageSharpenFilter::GPUImageSharpenFilter():GPUImageFilter(SHARPEN_VERTEX_SHADER, SHARPEN_FRAGMENT_SHADER) {
}

ben::ngp::GPUImageSharpenFilter::GPUImageSharpenFilter(JNIEnv *env) : GPUImageFilter(SHARPEN_VERTEX_SHADER, SHARPEN_FRAGMENT_SHADER,env) {
    initialize(env);
}

void ben::ngp::GPUImageSharpenFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "sharpness", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getSharpness", kTypeFloat, NULL);
    cacheMethod(env, "setSharpness", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageSharpenFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("sharpness", kTypeFloat, &sharpness);
}

const char *ben::ngp::GPUImageSharpenFilter::getCanonicalName() const {
    return JAVA_SHARPEN_FILTER;
}

void ben::ngp::GPUImageSharpenFilter::onInit() {
    GPUImageFilter::onInit();
    sharpnessLocation = glGetUniformLocation(getGlProgId(), "sharpness");
    imageWidthFactorLocation = glGetUniformLocation(getGlProgId(), "imageWidthFactor");
    imageHeightFactorLocation = glGetUniformLocation(getGlProgId(), "imageHeightFactor");
}

void ben::ngp::GPUImageSharpenFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setSharpness(sharpness);
}

void ben::ngp::GPUImageSharpenFilter::setSharpness(float sharpness) {
    GPUImageSharpenFilter::sharpness = sharpness;
    setFloat(sharpnessLocation, this->sharpness);
}

void ben::ngp::GPUImageSharpenFilter::onOutputSizeChanged(int width, int height) {
    GPUImageFilter::onOutputSizeChanged(width, height);
    setFloat(imageWidthFactorLocation, 1.0f / width);
    setFloat(imageHeightFactorLocation, 1.0f / height);
}
