//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_halftone_filter.hpp"

ben::ngp::GPUImageHalftoneFilter::GPUImageHalftoneFilter():GPUImageFilter(NO_FILTER_VERTEX_SHADER, HALFTONE_FRAGMENT_SHADER) {}

ben::ngp::GPUImageHalftoneFilter::GPUImageHalftoneFilter(JNIEnv *env) : GPUImageFilter(NO_FILTER_VERTEX_SHADER, HALFTONE_FRAGMENT_SHADER,env) {
    initialize(env);
}

void ben::ngp::GPUImageHalftoneFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "fractionalWidthOfAPixel", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getFractionalWidthOfAPixel", kTypeFloat, NULL);
    cacheMethod(env, "setFractionalWidthOfAPixel", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageHalftoneFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("fractionalWidthOfAPixel", kTypeFloat, &fractionalWidthOfAPixel);
}

const char *ben::ngp::GPUImageHalftoneFilter::getCanonicalName() const {
    return JAVA_HALFTONE_FILTER;
}

void ben::ngp::GPUImageHalftoneFilter::onInit() {
    GPUImageFilter::onInit();
    fractionalWidthOfPixelLocation = glGetUniformLocation(getGlProgId(), "fractionalWidthOfPixel");
    aspectRatioLocation = glGetUniformLocation(getGlProgId(), "aspectRatio");
}

void ben::ngp::GPUImageHalftoneFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setFractionalWidthOfAPixel(fractionalWidthOfAPixel);
    setAspectRatio(aspectRatio);
}

void ben::ngp::GPUImageHalftoneFilter::setFractionalWidthOfAPixel(float fractionalWidthOfAPixel) {
    GPUImageHalftoneFilter::fractionalWidthOfAPixel = fractionalWidthOfAPixel;
    setFloat(fractionalWidthOfPixelLocation, this->fractionalWidthOfAPixel);
}

void ben::ngp::GPUImageHalftoneFilter::setAspectRatio(float aspectRatio) {
    GPUImageHalftoneFilter::aspectRatio = aspectRatio;
    setFloat(aspectRatioLocation, this->aspectRatio);
}

void ben::ngp::GPUImageHalftoneFilter::onOutputSizeChanged(int width, int height) {
    GPUImageFilter::onOutputSizeChanged(width, height);
    setAspectRatio((float) height / (float) width);
}
