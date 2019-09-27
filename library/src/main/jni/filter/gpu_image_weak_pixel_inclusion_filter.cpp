//
// Created by ben622 on 2019/9/27.
//

#include "gpu_image_weak_pixel_inclusion_filter.hpp"

ben::ngp::GPUImageWeakPixelInclusionFilter::GPUImageWeakPixelInclusionFilter()
        : GPUImage3x3TextureSamplingFilter(WEAKPIXEL_FRAGMENT_SHADER) {}

ben::ngp::GPUImageWeakPixelInclusionFilter::GPUImageWeakPixelInclusionFilter(JNIEnv *env)
        : GPUImage3x3TextureSamplingFilter(env, WEAKPIXEL_FRAGMENT_SHADER) {}

void ben::ngp::GPUImageWeakPixelInclusionFilter::initialize(JNIEnv *env) {
    GPUImage3x3TextureSamplingFilter::initialize(env);
}

void ben::ngp::GPUImageWeakPixelInclusionFilter::mapFields() {
    GPUImage3x3TextureSamplingFilter::mapFields();
}

const char *ben::ngp::GPUImageWeakPixelInclusionFilter::getCanonicalName() const {
    return JAVA_WEAK_PIXEL_INCLUSION_FILTER;
}
