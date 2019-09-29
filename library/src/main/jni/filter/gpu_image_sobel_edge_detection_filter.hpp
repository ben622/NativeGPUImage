//
// Created by ben622 on 2019/9/29.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_SOBEL_EDGE_DETECTION_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_SOBEL_EDGE_DETECTION_FILTER_HPP

#include "gpu_image_filter_group.hpp"
#include "gpu_image_grayscale_filter.hpp"
#include "gpu_image_3x3_texture_sampling_filter.hpp"

#define JAVA_SOBEL_EDGE_DETECTION_FILTER "com/ben/android/library/filter/GPUImageSobelEdgeDetectionFilter"
static char *SOBEL_EDGE_DETECTION_SOURCE = GET_STR(
        precision
        mediump float;

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

        void main() {
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

            gl_FragColor = vec4(vec3(mag), 1.0);
        }
);
namespace ben {
    namespace ngp {
        class GPUImageSobelEdgeDetectionFilter : public GPUImageFilterGroup {
        private:
            float size;
        public:
            GPUImageSobelEdgeDetectionFilter(JNIEnv *env);

            virtual const char *getCanonicalName() const;

            void initialize(JNIEnv *env) override;

            void mapFields() override;

            void setSize(float size);

            float getSize() const;
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_SOBEL_EDGE_DETECTION_FILTER_HPP
