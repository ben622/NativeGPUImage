//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_sketch_filter.hpp"
#include "gpu_image_grayscale_filter.hpp"
#include "gpu_image_3x3_texture_sampling_filter.hpp"

ben::ngp::GPUImageSketchFilter::GPUImageSketchFilter():GPUImageFilterGroup() {}

ben::ngp::GPUImageSketchFilter::GPUImageSketchFilter(JNIEnv *env) : GPUImageFilterGroup(env) {
    initialize(env);
    addFilter(new GPUImageGrayscaleFilter());
    addFilter(new GPUImage3x3TextureSamplingFilter(SKETCH_FRAGMENT_SHADER));
}

const char *ben::ngp::GPUImageSketchFilter::getCanonicalName() const {
    return JAVA_SKETCH_FILTER;
}
