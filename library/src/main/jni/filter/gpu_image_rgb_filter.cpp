//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_rgb_filter.hpp"

ben::ngp::GPUImageRGBFilter::GPUImageRGBFilter(JNIEnv *env) : GPUImageFilter(NO_FILTER_VERTEX_SHADER, RGB_FRAGMENT_SHADER,env) {
    initialize(env);
    this->red = 1.0f;
    this->green = 1.0f;
    this->blue = 1.0f;
}

ben::ngp::GPUImageRGBFilter::GPUImageRGBFilter():GPUImageFilter(NO_FILTER_VERTEX_SHADER, RGB_FRAGMENT_SHADER) {
    this->red = 1.0f;
    this->green = 1.0f;
    this->blue = 1.0f;
}

void ben::ngp::GPUImageRGBFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "red", kTypeFloat);
    cacheField(env, "green", kTypeFloat);
    cacheField(env, "blue", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getRed", kTypeFloat, NULL);
    cacheMethod(env, "setRed", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getGreen", kTypeFloat, NULL);
    cacheMethod(env, "setGreen", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getBlue", kTypeFloat, NULL);
    cacheMethod(env, "setBlue", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageRGBFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("red", kTypeFloat, &red);
    mapField("green", kTypeFloat, &green);
    mapField("blue", kTypeFloat, &blue);
}

const char *ben::ngp::GPUImageRGBFilter::getCanonicalName() const {
    return JAVA_RGB_FILTER;
}

void ben::ngp::GPUImageRGBFilter::onInit() {
    GPUImageFilter::onInit();
    redLocation = glGetUniformLocation(getGlProgId(), "red");
    greenLocation = glGetUniformLocation(getGlProgId(), "green");
    blueLocation = glGetUniformLocation(getGlProgId(), "blue");
}

void ben::ngp::GPUImageRGBFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setRed(red);
    setGreen(green);
    setBlue(blue);
}

void ben::ngp::GPUImageRGBFilter::setRed(float red) {
    GPUImageRGBFilter::red = red;
    setFloat(redLocation, this->red);
}

void ben::ngp::GPUImageRGBFilter::setGreen(float green) {
    GPUImageRGBFilter::green = green;
    setFloat(greenLocation, this->green);
}

void ben::ngp::GPUImageRGBFilter::setBlue(float blue) {
    GPUImageRGBFilter::blue = blue;
    setFloat(blueLocation, this->blue);
}
