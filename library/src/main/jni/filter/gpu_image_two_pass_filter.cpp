//
// Created by ben622 on 2019/9/17.
//

#include "gpu_image_two_pass_filter.hpp"

ben::ngp::GPUImageTwoPassFilter::GPUImageTwoPassFilter(char *firstVertexShader,
                                                       char *firstFragmentShader,
                                                       char *secondVertexShader,
                                                       char *secondFragmentShader) {
    addFilter(new GPUImageFilter(firstVertexShader, firstFragmentShader));
    addFilter(new GPUImageFilter(secondVertexShader, secondFragmentShader));
}

const char *ben::ngp::GPUImageTwoPassFilter::getCanonicalName() const {
    return GPUImageFilterGroup::getCanonicalName();
}

ben::ngp::GPUImageTwoPassFilter::GPUImageTwoPassFilter(char *firstVertexShader,
                                                       char *firstFragmentShader,
                                                       char *secondVertexShader,
                                                       char *secondFragmentShader, JNIEnv *env):GPUImageFilterGroup(env){
    addFilter(new GPUImageFilter(firstVertexShader, firstFragmentShader));
    addFilter(new GPUImageFilter(secondVertexShader, secondFragmentShader));

}
