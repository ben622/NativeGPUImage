//
// Created by ben622 on 2019/9/29.
//

#include "gpu_image_alpha_blend_filter.hpp"

ben::ngp::GPUImageAlphaBlendFilter::GPUImageAlphaBlendFilter(float mix, JNIEnv *env)
        : GPUImageMixBlendFilter(ALPHA_BLEND_FRAGMENT_SHADER, env, mix) {
    initialize(env);

}

ben::ngp::GPUImageAlphaBlendFilter::GPUImageAlphaBlendFilter(JNIEnv *env)
        : GPUImageMixBlendFilter(ALPHA_BLEND_FRAGMENT_SHADER, env) {
    initialize(env);
}

void ben::ngp::GPUImageAlphaBlendFilter::initialize(JNIEnv *env) {
    GPUImageMixBlendFilter::initialize(env);
}

void ben::ngp::GPUImageAlphaBlendFilter::mapFields() {
    GPUImageMixBlendFilter::mapFields();
}

const char *ben::ngp::GPUImageAlphaBlendFilter::getCanonicalName() const {
    return JAVA_ALPHA_BLEND_FILTER;
}
