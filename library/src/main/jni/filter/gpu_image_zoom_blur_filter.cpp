//
// Created by ben622 on 2019/9/21.
//

#include "gpu_image_zoom_blur_filter.hpp"

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
    setPoint(blurCenterLocation, this->pointXF, this->pointYF);
}

void ben::ngp::GPUImageZoomBlurFilter::setBlurSize(int blurSize) {
    this->blurSize = blurSize;
    setFloat(blurSizeLocation, blurSize);
}
