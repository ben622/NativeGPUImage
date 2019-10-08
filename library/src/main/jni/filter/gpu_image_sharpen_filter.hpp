//
// Created by ben622 on 2019/10/8.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_SHARPEN_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_SHARPEN_FILTER_HPP

#include "gpu_image_filter.hpp"
#include "../include/jni/JniHelpersCommon.h"

#define JAVA_SHARPEN_FILTER "com/ben/android/library/filter/GPUImageSharpenFilter"
static char *SHARPEN_VERTEX_SHADER = GET_STR(
        attribute vec4 position;
        attribute vec4 inputTextureCoordinate;

        uniform float imageWidthFactor;
        uniform float imageHeightFactor;
        uniform float sharpness;

        varying vec2 textureCoordinate;
        varying vec2 leftTextureCoordinate;
        varying vec2 rightTextureCoordinate;
        varying vec2 topTextureCoordinate;
        varying vec2 bottomTextureCoordinate;

        varying float centerMultiplier;
        varying float edgeMultiplier;

        void main()
        {
            gl_Position = position;

            mediump vec2 widthStep = vec2(imageWidthFactor, 0.0);
            mediump vec2 heightStep = vec2(0.0, imageHeightFactor);

            textureCoordinate = inputTextureCoordinate.xy;
            leftTextureCoordinate = inputTextureCoordinate.xy - widthStep;
            rightTextureCoordinate = inputTextureCoordinate.xy + widthStep;
            topTextureCoordinate = inputTextureCoordinate.xy + heightStep;
            bottomTextureCoordinate = inputTextureCoordinate.xy - heightStep;

            centerMultiplier = 1.0 + 4.0 * sharpness;
            edgeMultiplier = sharpness;
        }
);

static char *SHARPEN_FRAGMENT_SHADER = GET_STR(
        precision highp float;

        varying highp vec2 textureCoordinate;
        varying highp vec2 leftTextureCoordinate;
        varying highp vec2 rightTextureCoordinate;
        varying highp vec2 topTextureCoordinate;
        varying highp vec2 bottomTextureCoordinate;

        varying highp float centerMultiplier;
        varying highp float edgeMultiplier;

        uniform sampler2D inputImageTexture;

        void main()
        {
            mediump vec3 textureColor = texture2D(inputImageTexture, textureCoordinate).rgb;
            mediump vec3 leftTextureColor = texture2D(inputImageTexture, leftTextureCoordinate).rgb;
            mediump vec3 rightTextureColor = texture2D(inputImageTexture, rightTextureCoordinate).rgb;
            mediump vec3 topTextureColor = texture2D(inputImageTexture, topTextureCoordinate).rgb;
            mediump vec3 bottomTextureColor = texture2D(inputImageTexture, bottomTextureCoordinate).rgb;

            gl_FragColor = vec4((textureColor * centerMultiplier - (leftTextureColor * edgeMultiplier + rightTextureColor * edgeMultiplier + topTextureColor * edgeMultiplier + bottomTextureColor * edgeMultiplier)), texture2D(inputImageTexture, bottomTextureCoordinate).w);
        }
);

namespace ben{
    namespace ngp{
        class GPUImageSharpenFilter:public GPUImageFilter{
        private:
            int sharpnessLocation;
            float sharpness;
            int imageWidthFactorLocation;
            int imageHeightFactorLocation;
        public:
            GPUImageSharpenFilter();

            GPUImageSharpenFilter(JNIEnv *env);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            virtual void onInit();

            virtual void onInitialized();

            void setSharpness(float sharpness);

            virtual void onOutputSizeChanged(int width, int height);
        };
    }
}

#endif //NATIVEGPUIMAGE_GPU_IMAGE_SHARPEN_FILTER_HPP
