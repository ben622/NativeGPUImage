//
// Created by ben622 on 2019/9/29.
//

#include "gpu_image_dissolve_blend_filter.hpp"

ben::ngp::GPUImageDissolveBlendFilter::GPUImageDissolveBlendFilter(JNIEnv *env)
    : GPUImageMixBlendFilter(DISSOLVE_BLEND_FRAGMENT_SHADER, env) {
    initialize(env);
}

ben::ngp::GPUImageDissolveBlendFilter::GPUImageDissolveBlendFilter(float mix, JNIEnv *env)
        : GPUImageMixBlendFilter(DISSOLVE_BLEND_FRAGMENT_SHADER, env, mix) {
    initialize(env);
}

void ben::ngp::GPUImageDissolveBlendFilter::initialize(JNIEnv *env) {
    GPUImageMixBlendFilter::initialize(env);
}

void ben::ngp::GPUImageDissolveBlendFilter::mapFields() {
    GPUImageMixBlendFilter::mapFields();
}

const char *ben::ngp::GPUImageDissolveBlendFilter::getCanonicalName() const {
    return JAVA_DISSOLVE_BLEND_FILTER;
}
