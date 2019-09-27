//
// Created by ben622 on 2019/9/27.
//

#include "gpu_image_vignette_filter.hpp"

ben::ngp::GPUImageVignetteFilter::GPUImageVignetteFilter() : GPUImageFilter(NO_FILTER_VERTEX_SHADER,
                                                                            VIGNETTING_FRAGMENT_SHADER) {
    this->vignetteCenterX = 0.5f;
    this->vignetteCenterY = 0.5f;
    this->vignetteColor = new float[3]{0.0f, 0.0f, 0.0f};
    this->vignetteStart = 0.3f;
    this->vignetteEnd = 0.75f;
}

ben::ngp::GPUImageVignetteFilter::GPUImageVignetteFilter(
        float vignetteCenterX,
        float vignetteCenterY,
        float *vignetteColor, float vignetteStart,
        float vignetteEnd) : GPUImageFilter(
        NO_FILTER_VERTEX_SHADER, VIGNETTING_FRAGMENT_SHADER), vignetteCenterX(vignetteCenterX),
                             vignetteCenterY(
                                     vignetteCenterY), vignetteColor(vignetteColor),
                             vignetteStart(vignetteStart), vignetteEnd(
                vignetteEnd) {
    this->vignetteCenterX = vignetteCenterX;
    this->vignetteCenterY = vignetteCenterY;
    this->vignetteColor = vignetteColor;
    this->vignetteStart = vignetteStart;
    this->vignetteEnd = vignetteEnd;
}

ben::ngp::GPUImageVignetteFilter::GPUImageVignetteFilter(JNIEnv *env) : GPUImageFilter(
        NO_FILTER_VERTEX_SHADER, VIGNETTING_FRAGMENT_SHADER, env) {
    initialize(env);
    this->vignetteCenterX = 0.5f;
    this->vignetteCenterY = 0.5f;
    this->vignetteColor = new float[3]{0.0f, 0.0f, 0.0f};
    this->vignetteStart = 0.3f;
    this->vignetteEnd = 0.75f;
}


void ben::ngp::GPUImageVignetteFilter::onInit() {
    GPUImageFilter::onInit();
    vignetteCenterLocation = glGetUniformLocation(getGlProgId(), "vignetteCenter");
    vignetteColorLocation = glGetUniformLocation(getGlProgId(), "vignetteColor");
    vignetteStartLocation = glGetUniformLocation(getGlProgId(), "vignetteStart");
    vignetteEndLocation = glGetUniformLocation(getGlProgId(), "vignetteEnd");
}

void ben::ngp::GPUImageVignetteFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setVignetteCenter(vignetteCenterX, vignetteCenterY);
    setVignetteColor(vignetteColor);
    setVignetteStart(vignetteStart);
    setVignetteEnd(vignetteEnd);
}

void
ben::ngp::GPUImageVignetteFilter::setVignetteCenter(float vignetteCenterX, float vignetteCenterY) {
    this->vignetteCenterX = vignetteCenterX;
    this->vignetteCenterY = vignetteCenterY;
    setPoint(vignetteCenterLocation, vignetteCenterX, vignetteCenterY);
}

void ben::ngp::GPUImageVignetteFilter::setVignetteColor(float *vignetteColor) {
    GPUImageVignetteFilter::vignetteColor = vignetteColor;
    setFloatVec3(vignetteColorLocation, this->vignetteColor);
}

void ben::ngp::GPUImageVignetteFilter::setVignetteStart(float vignetteStart) {
    GPUImageVignetteFilter::vignetteStart = vignetteStart;
    setFloat(vignetteStartLocation, this->vignetteStart);

}

void ben::ngp::GPUImageVignetteFilter::setVignetteEnd(float vignetteEnd) {
    GPUImageVignetteFilter::vignetteEnd = vignetteEnd;
    setFloat(vignetteEndLocation, this->vignetteEnd);
}

void ben::ngp::GPUImageVignetteFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "vignetteCenterX", kTypeFloat);
    cacheField(env, "vignetteCenterY", kTypeFloat);
    cacheField(env, "vignetteStart", kTypeFloat);
    cacheField(env, "vignetteEnd", kTypeFloat);
    cacheField(env, "vignetteColor", kTypeArray(kTypeFloat));
    cacheConstructor(env);
    cacheMethod(env, "getVignetteCenterX", kTypeFloat, NULL);
    cacheMethod(env, "setVignetteCenterX", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getVignetteCenterY", kTypeFloat, NULL);
    cacheMethod(env, "setVignetteCenterY", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getVignetteColor", kTypeArray(kTypeFloat), NULL);
    cacheMethod(env, "setVignetteColor", kTypeVoid, kTypeArray(kTypeFloat), NULL);
    cacheMethod(env, "getVignetteStart", kTypeFloat, NULL);
    cacheMethod(env, "setVignetteStart", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getVignetteEnd", kTypeFloat, NULL);
    cacheMethod(env, "setVignetteEnd", kTypeVoid, kTypeFloat, NULL);
    merge(this);

}

void ben::ngp::GPUImageVignetteFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("vignetteCenterX", kTypeFloat, &vignetteCenterX);
    mapField("vignetteCenterY", kTypeFloat, &vignetteCenterY);
    mapField("vignetteStart", kTypeFloat, &vignetteStart);
    mapField("vignetteEnd", kTypeFloat, &vignetteEnd);
    mapField("vignetteColor", kTypeFloat, &vignetteColor);
}

const char *ben::ngp::GPUImageVignetteFilter::getCanonicalName() const {
    return JAVA_VIGNETTE_FILTER;
}

