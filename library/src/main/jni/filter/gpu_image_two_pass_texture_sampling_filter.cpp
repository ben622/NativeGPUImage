//
// Created by ben622 on 2019/9/17.
//

#include "gpu_image_two_pass_texture_sampling_filter.hpp"

ben::ngp::GPUImageTwoPassTextureSamplingFilter::GPUImageTwoPassTextureSamplingFilter(
        char *firstVertexShader, char *firstFragmentShader, char *secondVertexShader,
        char *secondFragmentShader) : GPUImageTwoPassFilter(firstVertexShader, firstFragmentShader,
                                                            secondVertexShader,
                                                            secondFragmentShader) {}

void ben::ngp::GPUImageTwoPassTextureSamplingFilter::onOutputSizeChanged(int width, int height) {
    GPUImageFilterGroup::onOutputSizeChanged(width, height);
    initTexelOffsets();
}

void ben::ngp::GPUImageTwoPassTextureSamplingFilter::onInit() {
    GPUImageFilterGroup::onInit();
    initTexelOffsets();
}

float ben::ngp::GPUImageTwoPassTextureSamplingFilter::getVerticalTexelOffsetRatio() {
    return 1.0;
}

float ben::ngp::GPUImageTwoPassTextureSamplingFilter::getHorizontalTexelOffsetRatio() {
    return 1.0;
}

void ben::ngp::GPUImageTwoPassTextureSamplingFilter::initTexelOffsets() {
    float ratio = getHorizontalTexelOffsetRatio();
    GPUImageFilter* filter = getFilters()[0];
    int texelWidthOffsetLocation = glGetUniformLocation(filter->getGlProgId(), "texelWidthOffset");
    int texelHeightOffsetLocation = glGetUniformLocation(filter->getGlProgId(), "texelHeightOffset");
    filter->setFloat(texelWidthOffsetLocation, ratio / getOutputWidth());
    filter->setFloat(texelHeightOffsetLocation, 0);

    ratio = getVerticalTexelOffsetRatio();
    filter = getFilters()[1];
    texelWidthOffsetLocation = glGetUniformLocation(filter->getGlProgId(), "texelWidthOffset");
    texelHeightOffsetLocation = glGetUniformLocation(filter->getGlProgId(), "texelHeightOffset");
    filter->setFloat(texelWidthOffsetLocation, 0);
    filter->setFloat(texelHeightOffsetLocation, ratio / getOutputHeight());
}
