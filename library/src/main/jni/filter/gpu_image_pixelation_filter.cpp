//
// Created by ben622 on 2019/9/20.
//

#include "gpu_image_pixelation_filter.hpp"

ben::ngp::GPUImagePixelationFilter::GPUImagePixelationFilter():GPUImageFilter(NO_FILTER_VERTEX_SHADER, PIXELATION_FRAGMENT_SHADER) {
    this->pixel = 50.0;
}

void ben::ngp::GPUImagePixelationFilter::onOutputSizeChanged(int width, int height) {
    GPUImageFilter::onOutputSizeChanged(width, height);
    setFloat(imageWidthFactorLocation, 1.0f / width);
    setFloat(imageHeightFactorLocation, 1.0f / height);
}

void ben::ngp::GPUImagePixelationFilter::onInit() {
    GPUImageFilter::onInit();
    imageWidthFactorLocation = glGetUniformLocation(getGlProgId(), "imageWidthFactor");
    imageHeightFactorLocation = glGetUniformLocation(getGlProgId(), "imageHeightFactor");
    pixelLocation = glGetUniformLocation(getGlProgId(), "pixel");
}

void ben::ngp::GPUImagePixelationFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setPixel(pixel);
}

void ben::ngp::GPUImagePixelationFilter::setPixel(float pixel){
    this->pixel = pixel;
    setFloat(pixelLocation, this->pixel);
}

int ben::ngp::GPUImagePixelationFilter::getImageWidthFactorLocation() const {
    return imageWidthFactorLocation;
}

void ben::ngp::GPUImagePixelationFilter::setImageWidthFactorLocation(int imageWidthFactorLocation) {
    GPUImagePixelationFilter::imageWidthFactorLocation = imageWidthFactorLocation;
}

int ben::ngp::GPUImagePixelationFilter::getImageHeightFactorLocation() const {
    return imageHeightFactorLocation;
}

void
ben::ngp::GPUImagePixelationFilter::setImageHeightFactorLocation(int imageHeightFactorLocation) {
    GPUImagePixelationFilter::imageHeightFactorLocation = imageHeightFactorLocation;
}

float ben::ngp::GPUImagePixelationFilter::getPixel() const {
    return pixel;
}

int ben::ngp::GPUImagePixelationFilter::getPixelLocation() const {
    return pixelLocation;
}

void ben::ngp::GPUImagePixelationFilter::setPixelLocation(int pixelLocation) {
    GPUImagePixelationFilter::pixelLocation = pixelLocation;
}

