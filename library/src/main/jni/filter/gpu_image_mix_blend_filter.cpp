//
// Created by ben622 on 2019/9/29.
//

#include "gpu_image_mix_blend_filter.hpp"

ben::ngp::GPUImageMixBlendFilter::GPUImageMixBlendFilter(char *fragmentShader, JNIEnv *env)
        : GPUImageTwoInputFilter(fragmentShader, env) {}

ben::ngp::GPUImageMixBlendFilter::GPUImageMixBlendFilter(char *fragmentShader, JNIEnv *env,
                                                         float mix) : GPUImageTwoInputFilter(
        fragmentShader, env) {
    initialize(env);
    this->mix = mix;
}

void ben::ngp::GPUImageMixBlendFilter::onInit() {
    GPUImageTwoInputFilter::onInit();
    mixLocation = glGetUniformLocation(getGlProgId(), "mixturePercent");
}

void ben::ngp::GPUImageMixBlendFilter::onInitialized() {
    GPUImageTwoInputFilter::onInitialized();
    setMix(mix);
}

void ben::ngp::GPUImageMixBlendFilter::setMix(float mix) {
    GPUImageMixBlendFilter::mix = mix;
    setFloat(mixLocation, this->mix);
}

void ben::ngp::GPUImageMixBlendFilter::initialize(JNIEnv *env) {
    GPUImageTwoInputFilter::initialize(env);
    cacheField(env, "mix", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getMix", kTypeFloat, NULL);
    cacheMethod(env, "setMix", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageMixBlendFilter::mapFields() {
    GPUImageTwoInputFilter::mapFields();
    mapField("mix", kTypeFloat, &mix);
}

const char *ben::ngp::GPUImageMixBlendFilter::getCanonicalName() const {
    //don't register
    return JAVA_MIX_BLEND_FILTER;
}
