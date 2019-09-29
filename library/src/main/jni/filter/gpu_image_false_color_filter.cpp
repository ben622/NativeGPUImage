//
// Created by ben622 on 2019/9/29.
//

#include "gpu_image_false_color_filter.hpp"

ben::ngp::GPUImageFalseColorFilter::GPUImageFalseColorFilter() : GPUImageFilter(
        NO_FILTER_VERTEX_SHADER, FALSECOLOR_FRAGMENT_SHADER) {
    this->firstColor = new float[3]{firstRed, firstGreen, firstBlue};
    this->secondColor = new float[3]{secondRed, secondGreen,secondBlue};
}

ben::ngp::GPUImageFalseColorFilter::GPUImageFalseColorFilter(JNIEnv *env) : GPUImageFilter(
        NO_FILTER_VERTEX_SHADER, FALSECOLOR_FRAGMENT_SHADER, env) {
    initialize(env);
    this->firstColor = new float[3]{firstRed, firstGreen, firstBlue};
    this->secondColor = new float[3]{secondRed, secondGreen,secondBlue};
}

void ben::ngp::GPUImageFalseColorFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "firstRed", kTypeFloat);
    cacheField(env, "firstGreen", kTypeFloat);
    cacheField(env, "firstBlue", kTypeFloat);
    cacheField(env, "secondRed", kTypeFloat);
    cacheField(env, "secondGreen", kTypeFloat);
    cacheField(env, "secondBlue", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getFirstRed", kTypeFloat, NULL);
    cacheMethod(env, "setFirstRed", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getFirstGreen", kTypeFloat, NULL);
    cacheMethod(env, "setFirstGreen", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getFirstBlue", kTypeFloat, NULL);
    cacheMethod(env, "setFirstBlue", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getSecondRed", kTypeFloat, NULL);
    cacheMethod(env, "setSecondRed", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getSecondGreen", kTypeFloat, NULL);
    cacheMethod(env, "setSecondGreen", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getSecondBlue", kTypeFloat, NULL);
    cacheMethod(env, "setSecondBlue", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageFalseColorFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("firstRed", kTypeFloat, &firstRed);
    mapField("firstGreen", kTypeFloat, &firstGreen);
    mapField("firstBlue", kTypeFloat, &firstBlue);
    mapField("secondRed", kTypeFloat, &secondRed);
    mapField("secondGreen", kTypeFloat, &secondGreen);
    mapField("secondBlue", kTypeFloat, &secondBlue);
}

const char *ben::ngp::GPUImageFalseColorFilter::getCanonicalName() const {
    return JAVA_FALSE_COLOR_FILTER;
}

void ben::ngp::GPUImageFalseColorFilter::onInit() {
    GPUImageFilter::onInit();
    firstColorLocation = glGetUniformLocation(getGlProgId(), "firstColor");
    secondColorLocation = glGetUniformLocation(getGlProgId(), "secondColor");
}

void ben::ngp::GPUImageFalseColorFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    this->firstColor = new float[3]{firstRed, firstGreen, firstBlue};
    this->secondColor = new float[3]{secondRed, secondGreen,secondBlue};
    setFirstColor(firstColor);
    setSecondColor(secondColor);
}

void ben::ngp::GPUImageFalseColorFilter::setFirstColor(float *firstColor) {
    GPUImageFalseColorFilter::firstColor = firstColor;
    setFloatVec3(firstColorLocation, firstColor);
}

void ben::ngp::GPUImageFalseColorFilter::setSecondColor(float *secondColor) {
    GPUImageFalseColorFilter::secondColor = secondColor;
    setFloatVec3(secondColorLocation, secondColor);
}
