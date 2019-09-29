//
// Created by ben622 on 2019/9/29.
//

#include "gpu_image_3x3_convolution_filter.hpp"

ben::ngp::GPUImage3x3ConvolutionFilter::GPUImage3x3ConvolutionFilter()
        : GPUImage3x3TextureSamplingFilter(THREE_X_THREE_TEXTURE_SAMPLING_FRAGMENT_SHADER) {

    this->convolutionKernel = new float[9]{
            v1, v2, v3,
            v4, v5, v6,
            v7, v8, v9
    };
}

ben::ngp::GPUImage3x3ConvolutionFilter::GPUImage3x3ConvolutionFilter(JNIEnv *env)
        : GPUImage3x3TextureSamplingFilter(env, THREE_X_THREE_TEXTURE_SAMPLING_FRAGMENT_SHADER) {
    this->convolutionKernel = convolutionKernel;
    initialize(env);

}

ben::ngp::GPUImage3x3ConvolutionFilter::GPUImage3x3ConvolutionFilter(float *convolutionKernel)
        : GPUImage3x3TextureSamplingFilter(THREE_X_THREE_TEXTURE_SAMPLING_FRAGMENT_SHADER) {

    this->convolutionKernel = convolutionKernel;
}

ben::ngp::GPUImage3x3ConvolutionFilter::GPUImage3x3ConvolutionFilter(float *convolutionKernel,
                                                                     JNIEnv *env)
        : GPUImage3x3TextureSamplingFilter(env, THREE_X_THREE_TEXTURE_SAMPLING_FRAGMENT_SHADER) {
    this->convolutionKernel = convolutionKernel;
    initialize(env);
}


void ben::ngp::GPUImage3x3ConvolutionFilter::onInit() {
    GPUImage3x3TextureSamplingFilter::onInit();
    uniformConvolutionMatrix = glGetUniformLocation(getGlProgId(), "convolutionMatrix");
}

void ben::ngp::GPUImage3x3ConvolutionFilter::onInitialized() {
    GPUImage3x3TextureSamplingFilter::onInitialized();
    this->convolutionKernel = new float[9]{
            v1, v2, v3,
            v4, v5, v6,
            v7, v8, v9
    };
    setConvolutionKernel(convolutionKernel);
}

void ben::ngp::GPUImage3x3ConvolutionFilter::initialize(JNIEnv *env) {
    GPUImage3x3TextureSamplingFilter::initialize(env);
    cacheField(env, "v1", kTypeFloat);
    cacheField(env, "v2", kTypeFloat);
    cacheField(env, "v3", kTypeFloat);
    cacheField(env, "v4", kTypeFloat);
    cacheField(env, "v5", kTypeFloat);
    cacheField(env, "v6", kTypeFloat);
    cacheField(env, "v7", kTypeFloat);
    cacheField(env, "v8", kTypeFloat);
    cacheField(env, "v9", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getV1", kTypeFloat, NULL);
    cacheMethod(env, "setV1", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getV2", kTypeFloat, NULL);
    cacheMethod(env, "setV2", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getV3", kTypeFloat, NULL);
    cacheMethod(env, "setV3", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getV4", kTypeFloat, NULL);
    cacheMethod(env, "setV4", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getV5", kTypeFloat, NULL);
    cacheMethod(env, "setV5", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getV6", kTypeFloat, NULL);
    cacheMethod(env, "setV6", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getV7", kTypeFloat, NULL);
    cacheMethod(env, "setV7", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getV8", kTypeFloat, NULL);
    cacheMethod(env, "setV8", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getV9", kTypeFloat, NULL);
    cacheMethod(env, "setV9", kTypeVoid, kTypeFloat, NULL);
    merge(this);

}

void ben::ngp::GPUImage3x3ConvolutionFilter::mapFields() {
    GPUImage3x3TextureSamplingFilter::mapFields();
    mapField("v1", kTypeFloat, &v1);
    mapField("v2", kTypeFloat, &v2);
    mapField("v3", kTypeFloat, &v3);
    mapField("v4", kTypeFloat, &v4);
    mapField("v5", kTypeFloat, &v5);
    mapField("v6", kTypeFloat, &v6);
    mapField("v7", kTypeFloat, &v7);
    mapField("v8", kTypeFloat, &v8);
    mapField("v9", kTypeFloat, &v9);
}

const char *ben::ngp::GPUImage3x3ConvolutionFilter::getCanonicalName() const {
    return JAVA_3X3_CONVOLUTION_FILTER;
}

void ben::ngp::GPUImage3x3ConvolutionFilter::setConvolutionKernel(float *convolutionKernel) {
    GPUImage3x3ConvolutionFilter::convolutionKernel = convolutionKernel;
    setUniformMatrix3f(uniformConvolutionMatrix, this->convolutionKernel);
}
