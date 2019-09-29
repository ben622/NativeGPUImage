//
// Created by ben622 on 2019/9/29.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_TOON_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_TOON_FILTER_HPP

#include "gpu_image_3x3_texture_sampling_filter.hpp"

#define JAVA_TOON_FILTER "com/ben/android/library/filter/GPUImageToonFilter"
static char *TOON_FRAGMENT_SHADER = GET_STR(
        precision
        highp float;

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

        uniform
        sampler2D inputImageTexture;

        uniform
        highp float intensity;
        uniform
        highp float threshold;
        uniform
        highp float quantizationLevels;

        const highp vec3
        W = vec3(0.2125, 0.7154, 0.0721);

        void main() {
            vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

            float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;
            float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;
            float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;
            float bottomRightIntensity = texture2D(inputImageTexture,
                                                   bottomRightTextureCoordinate).r;
            float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;
            float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;
            float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;
            float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;
            float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity +
                      bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;
            float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity +
                      bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;

            float mag = length(vec2(h, v));

            vec3 posterizedImageColor =
                    floor((textureColor.rgb * quantizationLevels) + 0.5) / quantizationLevels;

            float thresholdTest = 1.0 - step(threshold, mag);

            gl_FragColor = vec4(posterizedImageColor * thresholdTest, textureColor.a);
        }
);
namespace ben {
    namespace ngp {
        class GPUImageToonFilter : public GPUImage3x3TextureSamplingFilter {
        private:
            float threshold;
            int thresholdLocation;
            float quantizationLevels;
            int quantizationLevelsLocation;
        public:
            GPUImageToonFilter();

            GPUImageToonFilter(JNIEnv *env);


        public:
            virtual void onInit();

            virtual void onInitialized();

        public:
            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

        public:
            void setThreshold(float threshold);

            void setQuantizationLevels(float quantizationLevels);
        };
    }
}


#endif //NATIVEGPUIMAGE_GPU_IMAGE_TOON_FILTER_HPP
