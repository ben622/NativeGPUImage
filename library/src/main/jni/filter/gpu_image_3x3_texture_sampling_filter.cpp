//
// Created by ben622 on 2019/9/27.
//

#include "gpu_image_3x3_texture_sampling_filter.hpp"

ben::ngp::GPUImage3x3TextureSamplingFilter::GPUImage3x3TextureSamplingFilter()
        : GPUImageFilter(THREE_X_THREE_TEXTURE_SAMPLING_VERTEX_SHADER, NO_FILTER_VERTEX_SHADER) {

}

ben::ngp::GPUImage3x3TextureSamplingFilter::GPUImage3x3TextureSamplingFilter(
        char *fragmentShader)
        : GPUImageFilter(THREE_X_THREE_TEXTURE_SAMPLING_VERTEX_SHADER, fragmentShader) {}

ben::ngp::GPUImage3x3TextureSamplingFilter::GPUImage3x3TextureSamplingFilter(JNIEnv *env)
        : GPUImageFilter(THREE_X_THREE_TEXTURE_SAMPLING_VERTEX_SHADER, NO_FILTER_VERTEX_SHADER,env) {
    initialize(env);
}

ben::ngp::GPUImage3x3TextureSamplingFilter::GPUImage3x3TextureSamplingFilter(JNIEnv *env,
                                                                             char *fragmentShader)
                                                                             :GPUImageFilter(THREE_X_THREE_TEXTURE_SAMPLING_VERTEX_SHADER, fragmentShader,env){
    initialize(env);

}

void ben::ngp::GPUImage3x3TextureSamplingFilter::onOutputSizeChanged(int width, int height) {
    GPUImageFilter::onOutputSizeChanged(width, height);
}

void ben::ngp::GPUImage3x3TextureSamplingFilter::onInit() {
    GPUImageFilter::onInit();
    uniformTexelWidthLocation = glGetUniformLocation(getGlProgId(), "texelWidth");
    uniformTexelHeightLocation = glGetUniformLocation(getGlProgId(), "texelHeight");
}

void ben::ngp::GPUImage3x3TextureSamplingFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    if (texelWidth != 0) {
        updateTexelValues();
    }
}

void ben::ngp::GPUImage3x3TextureSamplingFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "texelWidth", kTypeFloat);
    cacheField(env, "texelHeight", kTypeFloat);
    cacheField(env, "lineSize", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getTexelWidth", kTypeFloat, NULL);
    cacheMethod(env, "setTexelWidth", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getTexelHeight", kTypeFloat, NULL);
    cacheMethod(env, "setTexelHeight", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getLineSize", kTypeFloat, NULL);
    cacheMethod(env, "setLineSize", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImage3x3TextureSamplingFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("texelWidth", kTypeFloat, &texelWidth);
    mapField("texelHeight", kTypeFloat, &texelHeight);
    mapField("lineSize", kTypeFloat, &lineSize);
}

const char *ben::ngp::GPUImage3x3TextureSamplingFilter::getCanonicalName() const {
    return JAVA_3X3_TEXTURE_SAMPLING_FILTER;
}

void ben::ngp::GPUImage3x3TextureSamplingFilter::setTexelWidth(float texelWidth) {
    GPUImage3x3TextureSamplingFilter::texelWidth = texelWidth;
    hasOverriddenImageSizeFactor = true;
    setFloat(uniformTexelWidthLocation, texelWidth);
}

void ben::ngp::GPUImage3x3TextureSamplingFilter::setTexelHeight(float texelHeight) {
    GPUImage3x3TextureSamplingFilter::texelHeight = texelHeight;
    hasOverriddenImageSizeFactor = true;
    setFloat(uniformTexelHeightLocation, texelHeight);
}

void ben::ngp::GPUImage3x3TextureSamplingFilter::setLineSize(float lineSize) {
    GPUImage3x3TextureSamplingFilter::lineSize = lineSize;
    texelWidth = lineSize / getOutputWidth();
    texelHeight = lineSize / getOutputHeight();
    updateTexelValues();
}

void ben::ngp::GPUImage3x3TextureSamplingFilter::updateTexelValues() {
    setFloat(uniformTexelWidthLocation, texelWidth);
    setFloat(uniformTexelHeightLocation, texelHeight);

}
