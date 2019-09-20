//
// Created by ben622 on 2019/9/20.
//

#include "gpu_image_dilation_filter.hpp"


ben::ngp::GPUImageDilationFilter::GPUImageDilationFilter()
        : GPUImageTwoPassTextureSamplingFilter(VERTEX_SHADER_3, FRAGMENT_SHADER_3, VERTEX_SHADER_3,
                                               FRAGMENT_SHADER_3) {

}

ben::ngp::GPUImageDilationFilter::GPUImageDilationFilter(int radius)
        : GPUImageTwoPassTextureSamplingFilter(VERTEX_SHADER_1, FRAGMENT_SHADER_1, VERTEX_SHADER_1,
                                               FRAGMENT_SHADER_1) {

}
