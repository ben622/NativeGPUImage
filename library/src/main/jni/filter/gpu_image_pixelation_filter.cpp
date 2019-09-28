//
// Created by ben622 on 2019/9/20.
//

#include "gpu_image_pixelation_filter.hpp"


ben::ngp::GPUImagePixelationFilter::GPUImagePixelationFilter(JNIEnv *env) : GPUImageFilter(NO_FILTER_VERTEX_SHADER, PIXELATION_FRAGMENT_SHADER,env) {
    //必须在构造函数执行完以后才可以进行JNI操作
    initialize(env);
    this->pixel = 0.0;
}


ben::ngp::GPUImagePixelationFilter::GPUImagePixelationFilter():GPUImageFilter(NO_FILTER_VERTEX_SHADER, PIXELATION_FRAGMENT_SHADER) {
    this->pixel = 0.0;
}

void ben::ngp::GPUImagePixelationFilter::onOutputSizeChanged(int width, int height) {
    GPUImageFilter::onOutputSizeChanged(width, height);
    setFloat(imageWidthFactorLocation, 1.0f / width);
    setFloat(imageHeightFactorLocation, 1.0f / height);
}

void ben::ngp::GPUImagePixelationFilter::onInit() {
    GPUImageFilter::onInit();
    imageWidthFactorLocation = glGetUniformLocation(getGlProgId(), "imageWidthFactor");
    imageHeightFactorLocation = glGetUniformLocation(getGlProgId(), "imageHeightFactor");
    pixelLocation = glGetUniformLocation(getGlProgId(), "pixel");
}

void ben::ngp::GPUImagePixelationFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setPixel(pixel);
}

void ben::ngp::GPUImagePixelationFilter::setPixel(float pixel){
    this->pixel = pixel;
    setFloat(pixelLocation, this->pixel);
}

int ben::ngp::GPUImagePixelationFilter::getImageWidthFactorLocation() const {
    return imageWidthFactorLocation;
}

void ben::ngp::GPUImagePixelationFilter::setImageWidthFactorLocation(int imageWidthFactorLocation) {
    GPUImagePixelationFilter::imageWidthFactorLocation = imageWidthFactorLocation;
}

int ben::ngp::GPUImagePixelationFilter::getImageHeightFactorLocation() const {
    return imageHeightFactorLocation;
}

void
ben::ngp::GPUImagePixelationFilter::setImageHeightFactorLocation(int imageHeightFactorLocation) {
    GPUImagePixelationFilter::imageHeightFactorLocation = imageHeightFactorLocation;
}

float ben::ngp::GPUImagePixelationFilter::getPixel() const {
    return pixel;
}

int ben::ngp::GPUImagePixelationFilter::getPixelLocation() const {
    return pixelLocation;
}

void ben::ngp::GPUImagePixelationFilter::setPixelLocation(int pixelLocation) {
    GPUImagePixelationFilter::pixelLocation = pixelLocation;
}

const char *ben::ngp::GPUImagePixelationFilter::getCanonicalName() const {
    return JAVA_PIXELATION_FILTER;
}

void ben::ngp::GPUImagePixelationFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "pixel", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getPixel", kTypeFloat, NULL);
    cacheMethod(env, "setPixel", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImagePixelationFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("pixel", kTypeFloat, &pixel);

}
