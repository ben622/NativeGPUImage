//
// Created by ben622 on 2019/9/17.
//

#include "gpu_image_gaussian_blur_filter.hpp"

ben::ngp::GPUImageGaussianBlurFilter::GPUImageGaussianBlurFilter()
        : GPUImageTwoPassTextureSamplingFilter(VERTEX_SHADER, FRAGMENT_SHADER, VERTEX_SHADER,
                                               FRAGMENT_SHADER) {
    this->blurSize = 0.0;
}

ben::ngp::GPUImageGaussianBlurFilter::GPUImageGaussianBlurFilter(float blurSize)
        : GPUImageTwoPassTextureSamplingFilter(VERTEX_SHADER, FRAGMENT_SHADER, VERTEX_SHADER,
                                               FRAGMENT_SHADER) {
    this->blurSize = blurSize;

}


float ben::ngp::GPUImageGaussianBlurFilter::getVerticalTexelOffsetRatio() {
    return this->blurSize;
}

float ben::ngp::GPUImageGaussianBlurFilter::getHorizontalTexelOffsetRatio() {
    return this->blurSize;
}


void ben::ngp::GPUImageGaussianBlurFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setBlurSize(blurSize);
}

float ben::ngp::GPUImageGaussianBlurFilter::getBlurSize() const {
    return blurSize;
}

void ben::ngp::GPUImageGaussianBlurFilter::setBlurSize(float blurSize) {
    GPUImageGaussianBlurFilter::blurSize = blurSize;
    initTexelOffsets();
}


