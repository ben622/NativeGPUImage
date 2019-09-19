//
// Created by ben622 on 2019/9/17.
// 高斯模糊
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_GAUSSIAN_BLUR_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_GAUSSIAN_BLUR_FILTER_HPP

#include "gpu_image_two_pass_texture_sampling_filter.hpp"

static char *VERTEX_SHADER = "attribute vec4 position;"\
                             "attribute vec4 inputTextureCoordinate;"\
                             ""\
                             "const int GAUSSIAN_SAMPLES = 9;"\
                             ""\
                             "uniform float texelWidthOffset;"\
                             "uniform float texelHeightOffset;"\
                             ""\
                             "varying vec2 textureCoordinate;"\
                             "varying vec2 blurCoordinates[GAUSSIAN_SAMPLES];"\
                             ""\
                             "void main()"\
                             "{"\
                             "	gl_Position = position;"\
                             "	textureCoordinate = inputTextureCoordinate.xy;"\
                             "	"\
                             "	// Calculate the positions for the blur"\
                             "	int multiplier = 0;"\
                             "	vec2 blurStep;"\
                             "   vec2 singleStepOffset = vec2(texelHeightOffset, texelWidthOffset);"\
                             "    "\
                             "	for (int i = 0; i < GAUSSIAN_SAMPLES; i++)"\
                             "   {"\
                             "		multiplier = (i - ((GAUSSIAN_SAMPLES - 1) / 2));"\
                             "       // Blur in x (horizontal)"\
                             "       blurStep = float(multiplier) * singleStepOffset;"\
                             "		blurCoordinates[i] = inputTextureCoordinate.xy + blurStep;"\
                             "	}"\
                             "}";

static char *FRAGMENT_SHADER = "uniform sampler2D inputImageTexture;"\
                               ""\
                               "const lowp int GAUSSIAN_SAMPLES = 9;"\
                               ""\
                               "varying highp vec2 textureCoordinate;"\
                               "varying highp vec2 blurCoordinates[GAUSSIAN_SAMPLES];"\
                               ""\
                               "void main()"\
                               "{"\
                               "	lowp vec3 sum = vec3(0.0);"\
                               "   lowp vec4 fragColor=texture2D(inputImageTexture,textureCoordinate);"\
                               "	"\
                               "    sum += texture2D(inputImageTexture, blurCoordinates[0]).rgb * 0.05;"\
                               "    sum += texture2D(inputImageTexture, blurCoordinates[1]).rgb * 0.09;"\
                               "    sum += texture2D(inputImageTexture, blurCoordinates[2]).rgb * 0.12;"\
                               "    sum += texture2D(inputImageTexture, blurCoordinates[3]).rgb * 0.15;"\
                               "    sum += texture2D(inputImageTexture, blurCoordinates[4]).rgb * 0.18;"\
                               "    sum += texture2D(inputImageTexture, blurCoordinates[5]).rgb * 0.15;"\
                               "    sum += texture2D(inputImageTexture, blurCoordinates[6]).rgb * 0.12;"\
                               "    sum += texture2D(inputImageTexture, blurCoordinates[7]).rgb * 0.09;"\
                               "    sum += texture2D(inputImageTexture, blurCoordinates[8]).rgb * 0.05;"\
                               ""\
                               "	gl_FragColor = vec4(sum,fragColor.a);"\
                               "}";

/*
#define GET_STR(x) #x

static  char *VERTEX_SHADER = GET_STR(
        attribute
        vec4 position;
        attribute
        vec4 inputTextureCoordinate;

        const int GAUSSIAN_SAMPLES = 9;

        uniform float texelWidthOffset;
        uniform float texelHeightOffset;

        varying
        vec2 textureCoordinate;
        varying
        vec2 blurCoordinates[GAUSSIAN_SAMPLES];

        void main() {
            gl_Position = position;
            textureCoordinate = inputTextureCoordinate.xy;

            // Calculate the positions for the blur
            int multiplier = 0;
            vec2 blurStep;
            vec2 singleStepOffset = vec2(texelHeightOffset, texelWidthOffset);

            for (int i = 0; i < GAUSSIAN_SAMPLES; i++) {
                multiplier = (i - ((GAUSSIAN_SAMPLES - 1) / 2));
                // Blur in x (horizontal)
                blurStep = float(multiplier) * singleStepOffset;
                blurCoordinates[i] = inputTextureCoordinate.xy + blurStep;
            }
        }
);

static  char *FRAGMENT_SHADER = GET_STR(
        uniform sampler2D inputImageTexture;

        const lowp int GAUSSIAN_SAMPLES = 9;

        varying highp vec2 textureCoordinate;
        varying highp vec2 blurCoordinates[GAUSSIAN_SAMPLES];

        void main()
        {
            lowp vec3 sum = vec3(0.0);
            lowp vec4 fragColor=texture2D(inputImageTexture,textureCoordinate);

            sum += texture2D(inputImageTexture, blurCoordinates[0]).rgb * 0.05;
            sum += texture2D(inputImageTexture, blurCoordinates[1]).rgb * 0.09;
            sum += texture2D(inputImageTexture, blurCoordinates[2]).rgb * 0.12;
            sum += texture2D(inputImageTexture, blurCoordinates[3]).rgb * 0.15;
            sum += texture2D(inputImageTexture, blurCoordinates[4]).rgb * 0.18;
            sum += texture2D(inputImageTexture, blurCoordinates[5]).rgb * 0.15;
            sum += texture2D(inputImageTexture, blurCoordinates[6]).rgb * 0.12;
            sum += texture2D(inputImageTexture, blurCoordinates[7]).rgb * 0.09;
            sum += texture2D(inputImageTexture, blurCoordinates[8]).rgb * 0.05;

            gl_FragColor = vec4(sum,fragColor.a);
        }
);*/

namespace ben {
    namespace ngp {
        class GPUImageGaussianBlurFilter : public GPUImageTwoPassTextureSamplingFilter {
        private:
            float blurSize;
        public:
            float getBlurSize() const;

            void setBlurSize(float blurSize);

        public:
            GPUImageGaussianBlurFilter();

            GPUImageGaussianBlurFilter(float blurSize);

            float getVerticalTexelOffsetRatio() override;

            float getHorizontalTexelOffsetRatio() override;

            void onInitialized() override;

        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_GAUSSIAN_BLUR_FILTER_HPP
