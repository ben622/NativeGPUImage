//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_highlight_shadow_filter.hpp"

ben::ngp::GPUImageHighlightShadowFilter::GPUImageHighlightShadowFilter():GPUImageFilter(NO_FILTER_VERTEX_SHADER, HIGHLIGHT_SHADOW_FRAGMENT_SHADER) {}

ben::ngp::GPUImageHighlightShadowFilter::GPUImageHighlightShadowFilter(JNIEnv *env)
        : GPUImageFilter(NO_FILTER_VERTEX_SHADER, HIGHLIGHT_SHADOW_FRAGMENT_SHADER,env) {
    initialize(env);
}

void ben::ngp::GPUImageHighlightShadowFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "shadows", kTypeFloat);
    cacheField(env, "highlights", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getShadows", kTypeFloat, NULL);
    cacheMethod(env, "setShadows", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getHighlights", kTypeFloat, NULL);
    cacheMethod(env, "setHighlights", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageHighlightShadowFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("shadows", kTypeFloat, &shadows);
    mapField("highlights", kTypeFloat, &highlights);
}

const char *ben::ngp::GPUImageHighlightShadowFilter::getCanonicalName() const {
    return JAVA_HIGHLIGHT_SHADOW_FILTER;
}

void ben::ngp::GPUImageHighlightShadowFilter::onInit() {
    GPUImageFilter::onInit();
    highlightsLocation = glGetUniformLocation(getGlProgId(), "highlights");
    shadowsLocation = glGetUniformLocation(getGlProgId(), "shadows");
}

void ben::ngp::GPUImageHighlightShadowFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setHighlights(highlights);
    setShadows(shadows);
}

void ben::ngp::GPUImageHighlightShadowFilter::setShadows(float shadows) {
    GPUImageHighlightShadowFilter::shadows = shadows;
    setFloat(shadowsLocation, this->shadows);
}

void ben::ngp::GPUImageHighlightShadowFilter::setHighlights(float highlights) {
    GPUImageHighlightShadowFilter::highlights = highlights;
    setFloat(highlightsLocation, this->highlights);
}
