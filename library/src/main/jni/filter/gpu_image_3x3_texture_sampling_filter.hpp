//
// Created by ben622 on 2019/9/27.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_3X3_TEXTURE_SAMPLING_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_3X3_TEXTURE_SAMPLING_FILTER_HPP

#include "gpu_image_filter.hpp"

#define JAVA_3X3_TEXTURE_SAMPLING_FILTER "com/ben/android/library/filter/GPUImage3x3TextureSamplingFilter"

static char *THREE_X_THREE_TEXTURE_SAMPLING_VERTEX_SHADER = GET_STR(
        attribute
        vec4 position;
        attribute
        vec4 inputTextureCoordinate;

        uniform
        highp float texelWidth;
        uniform
        highp float texelHeight;

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
            gl_Position = position;

            vec2 widthStep = vec2(texelWidth, 0.0);
            vec2 heightStep = vec2(0.0, texelHeight);
            vec2 widthHeightStep = vec2(texelWidth, texelHeight);
            vec2 widthNegativeHeightStep = vec2(texelWidth, -texelHeight);

            textureCoordinate = inputTextureCoordinate.xy;
            leftTextureCoordinate = inputTextureCoordinate.xy - widthStep;
            rightTextureCoordinate = inputTextureCoordinate.xy + widthStep;

            topTextureCoordinate = inputTextureCoordinate.xy - heightStep;
            topLeftTextureCoordinate = inputTextureCoordinate.xy - widthHeightStep;
            topRightTextureCoordinate = inputTextureCoordinate.xy + widthNegativeHeightStep;

            bottomTextureCoordinate = inputTextureCoordinate.xy + heightStep;
            bottomLeftTextureCoordinate = inputTextureCoordinate.xy - widthNegativeHeightStep;
            bottomRightTextureCoordinate = inputTextureCoordinate.xy + widthHeightStep;
        }
);
namespace ben {
    namespace ngp {
        class GPUImage3x3TextureSamplingFilter : public GPUImageFilter {
        private:
            int uniformTexelWidthLocation;
            int uniformTexelHeightLocation;
            bool hasOverriddenImageSizeFactor = false;
            float texelWidth;
            float texelHeight;
            float lineSize = 1.0f;
        public:
            GPUImage3x3TextureSamplingFilter();

            GPUImage3x3TextureSamplingFilter(char *fragmentShader);

            GPUImage3x3TextureSamplingFilter(JNIEnv *env);

            GPUImage3x3TextureSamplingFilter(JNIEnv *env, char *fragmentShader);


        public:
            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

        public:
            virtual void onOutputSizeChanged(int width, int height);

            virtual void onInit();

            virtual void onInitialized();

        public:
            void updateTexelValues();

            void setTexelWidth(float texelWidth);

            void setTexelHeight(float texelHeight);

            void setLineSize(float lineSize);
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_3X3_TEXTURE_SAMPLING_FILTER_HPP
