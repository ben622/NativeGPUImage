//
// Created by ben622 on 2019/9/21.
//

#include "gpu_image_zoom_blur_filter.hpp"

ben::ngp::GPUImageZoomBlurFilter::GPUImageZoomBlurFilter(JNIEnv *env) : GPUImageFilter(
        NO_FILTER_VERTEX_SHADER, ZOOM_BLUR_FRAGMENT_SHADER, env) {
    //必须在构造函数执行完以后才可以进行JNI操作
    initialize(env);
    this->pointXF = 0.5f;
    this->pointYF = 0.5f;
    this->blurSize = 1.0f;
}

ben::ngp::GPUImageZoomBlurFilter::GPUImageZoomBlurFilter()
        : GPUImageFilter(NO_FILTER_VERTEX_SHADER, ZOOM_BLUR_FRAGMENT_SHADER) {
    this->pointXF = 0.5f;
    this->pointYF = 0.5f;
    this->blurSize = 1.0f;
}

void ben::ngp::GPUImageZoomBlurFilter::onInit() {
    GPUImageFilter::onInit();
    blurCenterLocation = glGetUniformLocation(getGlProgId(), "blurCenter");
    blurSizeLocation = glGetUniformLocation(getGlProgId(), "blurSize");
}

void ben::ngp::GPUImageZoomBlurFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setBlurCenter(this->pointXF, this->pointYF);
    setBlurSize(blurSize);
}

void ben::ngp::GPUImageZoomBlurFilter::setBlurCenter(float pointXF, float pointYF) {
    this->pointXF = pointXF;
    this->pointYF = pointYF;
    setPoint(blurCenterLocation, 0.5f, 0.5f);
}

void ben::ngp::GPUImageZoomBlurFilter::setBlurSize(int blurSize) {
    this->blurSize = blurSize;
    setFloat(blurSizeLocation, 1.0f);
}

const char *ben::ngp::GPUImageZoomBlurFilter::getCanonicalName() const {
    return JAVA_ZOOM_BLUR_FILTER;
}

void ben::ngp::GPUImageZoomBlurFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "pointXF", kTypeFloat);
    cacheField(env, "pointYF", kTypeFloat);
    cacheField(env, "blurSize", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getPointXF", kTypeFloat, NULL);
    cacheMethod(env, "setPointXF", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getPointYF", kTypeFloat, NULL);
    cacheMethod(env, "setPointYF", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getBlurSize", kTypeFloat, NULL);
    cacheMethod(env, "setBlurSize", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageZoomBlurFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("pointXF", kTypeFloat, &pointXF);
    mapField("pointYF", kTypeFloat, &pointYF);
    mapField("blurSize", kTypeFloat, &blurSize);
}

void ben::ngp::GPUImageZoomBlurFilter::onDrawPre() {
    GPUImageFilter::onDrawPre();
}


