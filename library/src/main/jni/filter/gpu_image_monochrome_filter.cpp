//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_monochrome_filter.hpp"

ben::ngp::GPUImageMonochromeFilter::GPUImageMonochromeFilter(JNIEnv *env) : GPUImageFilter(NO_FILTER_VERTEX_SHADER, MONOCHROME_FRAGMENT_SHADER,env) {
    initialize(env);
    this->color = new float[4]{v1,v2,v3};
}

ben::ngp::GPUImageMonochromeFilter::GPUImageMonochromeFilter():GPUImageFilter(NO_FILTER_VERTEX_SHADER, MONOCHROME_FRAGMENT_SHADER) {
    this->color = new float[4]{v1,v2,v3};
}

void ben::ngp::GPUImageMonochromeFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "intensity", kTypeFloat);
    cacheField(env, "v1", kTypeFloat);
    cacheField(env, "v2", kTypeFloat);
    cacheField(env, "v3", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getIntensity", kTypeFloat, NULL);
    cacheMethod(env, "setIntensity", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getV1", kTypeFloat, NULL);
    cacheMethod(env, "setV1", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getV2", kTypeFloat, NULL);
    cacheMethod(env, "setV2", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getV3", kTypeFloat, NULL);
    cacheMethod(env, "setV3", kTypeVoid, kTypeFloat, NULL);
    merge(this);

}

void ben::ngp::GPUImageMonochromeFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("intensity", kTypeFloat, &intensity);
    mapField("v1", kTypeFloat, &v1);
    mapField("v2", kTypeFloat, &v2);
    mapField("v3", kTypeFloat, &v3);
}

const char *ben::ngp::GPUImageMonochromeFilter::getCanonicalName() const {
    return JAVA_MONOCHROME_FILTER;
}

void ben::ngp::GPUImageMonochromeFilter::onInit() {
    GPUImageFilter::onInit();
    intensityLocation = glGetUniformLocation(getGlProgId(), "intensity");
    filterColorLocation = glGetUniformLocation(getGlProgId(), "filterColor");
}

void ben::ngp::GPUImageMonochromeFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setIntensity(this->intensity);
    this->color = new float[4]{v1,v2,v3};
    setColor(this->color);
}

void ben::ngp::GPUImageMonochromeFilter::setIntensity(float intensity) {
    GPUImageMonochromeFilter::intensity = intensity;
    setFloat(intensityLocation, this->intensity);
}

void ben::ngp::GPUImageMonochromeFilter::setColor(float *color) {
    GPUImageMonochromeFilter::color = color;
    setFloatVec3(filterColorLocation, color);
}
