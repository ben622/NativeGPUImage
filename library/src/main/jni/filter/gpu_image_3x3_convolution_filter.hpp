//
// Created by ben622 on 2019/9/29.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_3X3_CONVOLUTION_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_3X3_CONVOLUTION_FILTER_HPP

#include "gpu_image_3x3_texture_sampling_filter.hpp"
#include "../include/jni/JniHelpersCommon.h"

#define JAVA_3X3_CONVOLUTION_FILTER "com/ben/android/library/filter/GPUImage3x3ConvolutionFilter"
static char *THREE_X_THREE_TEXTURE_SAMPLING_FRAGMENT_SHADER = GET_STR(
        precision
        highp float;

        uniform
        sampler2D inputImageTexture;

        uniform
        mediump
        mat3 convolutionMatrix;

        varying
        vec2 textureCoordinate;
        varying
        vec2 leftTextureCoordinate;
        varying
        vec2 rightTextureCoordinate;

        varying
        vec2 topTextureCoordinate;
        varying
        vec2 topLeftTextureCoordinate;
        varying
        vec2 topRightTextureCoordinate;

        varying
        vec2 bottomTextureCoordinate;
        varying
        vec2 bottomLeftTextureCoordinate;
        varying
        vec2 bottomRightTextureCoordinate;

        void main() {
            mediump
            vec4 bottomColor = texture2D(inputImageTexture, bottomTextureCoordinate);
            mediump
            vec4 bottomLeftColor = texture2D(inputImageTexture, bottomLeftTextureCoordinate);
            mediump
            vec4 bottomRightColor = texture2D(inputImageTexture, bottomRightTextureCoordinate);
            mediump
            vec4 centerColor = texture2D(inputImageTexture, textureCoordinate);
            mediump
            vec4 leftColor = texture2D(inputImageTexture, leftTextureCoordinate);
            mediump
            vec4 rightColor = texture2D(inputImageTexture, rightTextureCoordinate);
            mediump
            vec4 topColor = texture2D(inputImageTexture, topTextureCoordinate);
            mediump
            vec4 topRightColor = texture2D(inputImageTexture, topRightTextureCoordinate);
            mediump
            vec4 topLeftColor = texture2D(inputImageTexture, topLeftTextureCoordinate);

            mediump
            vec4 resultColor =
                    topLeftColor * convolutionMatrix[0][0] + topColor * convolutionMatrix[0][1] +
                    topRightColor * convolutionMatrix[0][2];
            resultColor +=
                    leftColor * convolutionMatrix[1][0] + centerColor * convolutionMatrix[1][1] +
                    rightColor * convolutionMatrix[1][2];
            resultColor += bottomLeftColor * convolutionMatrix[2][0] +
                           bottomColor * convolutionMatrix[2][1] +
                           bottomRightColor * convolutionMatrix[2][2];

            gl_FragColor = resultColor;
        }
);
namespace ben {
    namespace ngp {
        class GPUImage3x3ConvolutionFilter : public GPUImage3x3TextureSamplingFilter {
        private:
            float *convolutionKernel;
            int uniformConvolutionMatrix;
            float v1=0.0f;
            float v2=0.0f;
            float v3=0.0f;
            float v4=0.0f;
            float v5=1.0f;
            float v6=0.0f;
            float v7=0.0f;
            float v8=0.0f;
            float v9=0.0f;

        public:
            GPUImage3x3ConvolutionFilter();
            GPUImage3x3ConvolutionFilter(JNIEnv *env);
            GPUImage3x3ConvolutionFilter(float *convolutionKernel);
            GPUImage3x3ConvolutionFilter(float *convolutionKernel,JNIEnv *env);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            virtual void onInit();

            virtual void onInitialized();

            void setConvolutionKernel(float *convolutionKernel);

        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_3X3_CONVOLUTION_FILTER_HPP
