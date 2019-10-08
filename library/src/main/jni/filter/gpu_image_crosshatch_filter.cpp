//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_crosshatch_filter.hpp"

ben::ngp::GPUImageCrosshatchFilter::GPUImageCrosshatchFilter():GPUImageFilter(NO_FILTER_VERTEX_SHADER, CROSSHATCH_FRAGMENT_SHADER) {}

ben::ngp::GPUImageCrosshatchFilter::GPUImageCrosshatchFilter(JNIEnv *env) : GPUImageFilter(NO_FILTER_VERTEX_SHADER, CROSSHATCH_FRAGMENT_SHADER,env) {
    initialize(env);
}

void ben::ngp::GPUImageCrosshatchFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "crossHatchSpacing", kTypeFloat);
    cacheField(env, "lineWidth", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getCrossHatchSpacing", kTypeFloat, NULL);
    cacheMethod(env, "setCrossHatchSpacing", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getLineWidth", kTypeFloat, NULL);
    cacheMethod(env, "setLineWidth", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageCrosshatchFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("crossHatchSpacing", kTypeFloat, &crossHatchSpacing);
    mapField("lineWidth", kTypeFloat, &lineWidth);
}

const char *ben::ngp::GPUImageCrosshatchFilter::getCanonicalName() const {
    return JAVA_CROSSHATCH_FILTER;
}

void ben::ngp::GPUImageCrosshatchFilter::onInit() {
    GPUImageFilter::onInit();
    crossHatchSpacingLocation = glGetUniformLocation(getGlProgId(), "crossHatchSpacing");
    lineWidthLocation = glGetUniformLocation(getGlProgId(), "lineWidth");
}

void ben::ngp::GPUImageCrosshatchFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setCrossHatchSpacing(crossHatchSpacing);
    setLineWidth(lineWidth);
}

void ben::ngp::GPUImageCrosshatchFilter::setCrossHatchSpacing(float crossHatchSpacing) {
    float singlePixelSpacing;
    if (getOutputWidth() != 0) {
        singlePixelSpacing = 1.0f / (float) getOutputWidth();
    } else {
        singlePixelSpacing = 1.0f / 2048.0f;
    }

    if (crossHatchSpacing < singlePixelSpacing) {
        this->crossHatchSpacing = singlePixelSpacing;
    } else {
        this->crossHatchSpacing = crossHatchSpacing;
    }

    setFloat(crossHatchSpacingLocation, this->crossHatchSpacing);
}

void ben::ngp::GPUImageCrosshatchFilter::setLineWidth(float lineWidth) {
    GPUImageCrosshatchFilter::lineWidth = lineWidth;
    setFloat(lineWidthLocation, this->lineWidth);
}
