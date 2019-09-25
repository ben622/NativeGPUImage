//
// Created by ben622 on 2019/9/20.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_DILATION_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_DILATION_FILTER_HPP

#include "gpu_image_two_pass_texture_sampling_filter.hpp"
#define JAVA_DILATION_FILTER "com/ben/android/library/filter/DilationFilter"

#define GET_STR(x) #x
static char *VERTEX_SHADER_1 = GET_STR(
        attribute vec4 position;
        attribute vec2 inputTextureCoordinate;

        uniform float texelWidthOffset;
        uniform float texelHeightOffset;

        varying vec2 centerTextureCoordinate;
        varying vec2 oneStepPositiveTextureCoordinate;
        varying vec2 oneStepNegativeTextureCoordinate;

        void main()
        {
            gl_Position = position;

            vec2 offset = vec2(texelWidthOffset, texelHeightOffset);

            centerTextureCoordinate = inputTextureCoordinate;
            oneStepNegativeTextureCoordinate = inputTextureCoordinate - offset;
            oneStepPositiveTextureCoordinate = inputTextureCoordinate + offset;
        }
    );
static char *VERTEX_SHADER_2 = GET_STR(
        attribute vec4 position;
        attribute vec2 inputTextureCoordinate;

        uniform float texelWidthOffset;
        uniform float texelHeightOffset;

        varying vec2 centerTextureCoordinate;
        varying vec2 oneStepPositiveTextureCoordinate;
        varying vec2 oneStepNegativeTextureCoordinate;
        varying vec2 twoStepsPositiveTextureCoordinate;
        varying vec2 twoStepsNegativeTextureCoordinate;

        void main()
        {
            gl_Position = position;

            vec2 offset = vec2(texelWidthOffset, texelHeightOffset);

            centerTextureCoordinate = inputTextureCoordinate;
            oneStepNegativeTextureCoordinate = inputTextureCoordinate - offset;
            oneStepPositiveTextureCoordinate = inputTextureCoordinate + offset;
            twoStepsNegativeTextureCoordinate = inputTextureCoordinate - (offset * 2.0);
            twoStepsPositiveTextureCoordinate = inputTextureCoordinate + (offset * 2.0);
        }
    );
static char *VERTEX_SHADER_3 = GET_STR(
        attribute vec4 position;
        attribute vec2 inputTextureCoordinate;

        uniform float texelWidthOffset;
        uniform float texelHeightOffset;

        varying vec2 centerTextureCoordinate;
        varying vec2 oneStepPositiveTextureCoordinate;
        varying vec2 oneStepNegativeTextureCoordinate;
        varying vec2 twoStepsPositiveTextureCoordinate;
        varying vec2 twoStepsNegativeTextureCoordinate;
        varying vec2 threeStepsPositiveTextureCoordinate;
        varying vec2 threeStepsNegativeTextureCoordinate;

        void main()
        {
            gl_Position = position;

            vec2 offset = vec2(texelWidthOffset, texelHeightOffset);

            centerTextureCoordinate = inputTextureCoordinate;
            oneStepNegativeTextureCoordinate = inputTextureCoordinate - offset;
            oneStepPositiveTextureCoordinate = inputTextureCoordinate + offset;
            twoStepsNegativeTextureCoordinate = inputTextureCoordinate - (offset * 2.0);
            twoStepsPositiveTextureCoordinate = inputTextureCoordinate + (offset * 2.0);
            threeStepsNegativeTextureCoordinate = inputTextureCoordinate - (offset * 3.0);
            threeStepsPositiveTextureCoordinate = inputTextureCoordinate + (offset * 3.0);
        }
    );
static char *VERTEX_SHADER_4 = GET_STR(
        attribute vec4 position;
        attribute vec2 inputTextureCoordinate;

        uniform float texelWidthOffset;
        uniform float texelHeightOffset;

        varying vec2 centerTextureCoordinate;
        varying vec2 oneStepPositiveTextureCoordinate;
        varying vec2 oneStepNegativeTextureCoordinate;
        varying vec2 twoStepsPositiveTextureCoordinate;
        varying vec2 twoStepsNegativeTextureCoordinate;
        varying vec2 threeStepsPositiveTextureCoordinate;
        varying vec2 threeStepsNegativeTextureCoordinate;
        varying vec2 fourStepsPositiveTextureCoordinate;
        varying vec2 fourStepsNegativeTextureCoordinate;

        void main()
        {
            gl_Position = position;

            vec2 offset = vec2(texelWidthOffset, texelHeightOffset);

            centerTextureCoordinate = inputTextureCoordinate;
            oneStepNegativeTextureCoordinate = inputTextureCoordinate - offset;
            oneStepPositiveTextureCoordinate = inputTextureCoordinate + offset;
            twoStepsNegativeTextureCoordinate = inputTextureCoordinate - (offset * 2.0);
            twoStepsPositiveTextureCoordinate = inputTextureCoordinate + (offset * 2.0);
            threeStepsNegativeTextureCoordinate = inputTextureCoordinate - (offset * 3.0);
            threeStepsPositiveTextureCoordinate = inputTextureCoordinate + (offset * 3.0);
            fourStepsNegativeTextureCoordinate = inputTextureCoordinate - (offset * 4.0);
            fourStepsPositiveTextureCoordinate = inputTextureCoordinate + (offset * 4.0);
        }
);
static char *FRAGMENT_SHADER_1 = GET_STR(
        precision lowp float;

        varying vec2 centerTextureCoordinate;
        varying vec2 oneStepPositiveTextureCoordinate;
        varying vec2 oneStepNegativeTextureCoordinate;

        uniform sampler2D inputImageTexture;

        void main()
        {
            float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;
            float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;
            float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;

            lowp float maxValue = max(centerIntensity, oneStepPositiveIntensity);
            maxValue = max(maxValue, oneStepNegativeIntensity);

            gl_FragColor = vec4(vec3(maxValue), 1.0);
        }
);
static char *FRAGMENT_SHADER_2 = GET_STR(
        precision lowp float;

        varying vec2 centerTextureCoordinate;
        varying vec2 oneStepPositiveTextureCoordinate;
        varying vec2 oneStepNegativeTextureCoordinate;
        varying vec2 twoStepsPositiveTextureCoordinate;
        varying vec2 twoStepsNegativeTextureCoordinate;

        uniform sampler2D inputImageTexture;

        void main()
        {
            float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;
            float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;
            float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;
            float twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate).r;
            float twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate).r;

            lowp float maxValue = max(centerIntensity, oneStepPositiveIntensity);
            maxValue = max(maxValue, oneStepNegativeIntensity);
            maxValue = max(maxValue, twoStepsPositiveIntensity);
            maxValue = max(maxValue, twoStepsNegativeIntensity);

            gl_FragColor = vec4(vec3(maxValue), 1.0);
        }
);
static char *FRAGMENT_SHADER_3 = GET_STR(
        precision lowp float;

        varying vec2 centerTextureCoordinate;
        varying vec2 oneStepPositiveTextureCoordinate;
        varying vec2 oneStepNegativeTextureCoordinate;
        varying vec2 twoStepsPositiveTextureCoordinate;
        varying vec2 twoStepsNegativeTextureCoordinate;
        varying vec2 threeStepsPositiveTextureCoordinate;
        varying vec2 threeStepsNegativeTextureCoordinate;

        uniform sampler2D inputImageTexture;

        void main()
        {
            float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;
            float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;
            float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;
            float twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate).r;
            float twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate).r;
            float threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate).r;
            float threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate).r;

            lowp float maxValue = max(centerIntensity, oneStepPositiveIntensity);
            maxValue = max(maxValue, oneStepNegativeIntensity);
            maxValue = max(maxValue, twoStepsPositiveIntensity);
            maxValue = max(maxValue, twoStepsNegativeIntensity);
            maxValue = max(maxValue, threeStepsPositiveIntensity);
            maxValue = max(maxValue, threeStepsNegativeIntensity);

            gl_FragColor = vec4(vec3(maxValue), 1.0);
        }
);
static char *FRAGMENT_SHADER_4 = GET_STR(
        precision lowp float;

        varying vec2 centerTextureCoordinate;
        varying vec2 oneStepPositiveTextureCoordinate;
        varying vec2 oneStepNegativeTextureCoordinate;
        varying vec2 twoStepsPositiveTextureCoordinate;
        varying vec2 twoStepsNegativeTextureCoordinate;
        varying vec2 threeStepsPositiveTextureCoordinate;
        varying vec2 threeStepsNegativeTextureCoordinate;
        varying vec2 fourStepsPositiveTextureCoordinate;
        varying vec2 fourStepsNegativeTextureCoordinate;

        uniform sampler2D inputImageTexture;

        void main()
        {
            float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;
            float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;
            float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;
            float twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate).r;
            float twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate).r;
            float threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate).r;
            float threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate).r;
            float fourStepsPositiveIntensity = texture2D(inputImageTexture, fourStepsPositiveTextureCoordinate).r;
            float fourStepsNegativeIntensity = texture2D(inputImageTexture, fourStepsNegativeTextureCoordinate).r;

            lowp float maxValue = max(centerIntensity, oneStepPositiveIntensity);
            maxValue = max(maxValue, oneStepNegativeIntensity);
            maxValue = max(maxValue, twoStepsPositiveIntensity);
            maxValue = max(maxValue, twoStepsNegativeIntensity);
            maxValue = max(maxValue, threeStepsPositiveIntensity);
            maxValue = max(maxValue, threeStepsNegativeIntensity);
            maxValue = max(maxValue, fourStepsPositiveIntensity);
            maxValue = max(maxValue, fourStepsNegativeIntensity);

            gl_FragColor = vec4(vec3(maxValue), 1.0);
        }
);
namespace ben{
    namespace ngp{
        class GPUImageDilationFilter:public ben::ngp::GPUImageTwoPassTextureSamplingFilter {
        private:
            int radius;
        public:
            GPUImageDilationFilter();

            GPUImageDilationFilter(int radius);

            GPUImageDilationFilter(JNIEnv *env);

        public:
            void initialize(JNIEnv *env) override;

            void mapFields() override;

            const char *getCanonicalName() const override;

        public:
            int getRadius() const;

            void setRadius(int radius);
        };
    }
}

#endif //NATIVEGPUIMAGE_GPU_IMAGE_DILATION_FILTER_HPP
