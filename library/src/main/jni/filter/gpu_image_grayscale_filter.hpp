//
// Created by ben622 on 2019/9/29.
//
#ifndef NATIVEGPUIMAGE_GPU_IMAGE_GRAYSCALE_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_GRAYSCALE_FILTER_HPP

#include "gpu_image_filter.hpp"
#define JAVA_GRAYSCALE_FILTER "com/ben/android/library/filter/GPUImageGrayscaleFilter"
static char *GRAYSCALE_FRAGMENT_SHADER = GET_STR(
        precision highp float;

        varying vec2 textureCoordinate;

        uniform sampler2D inputImageTexture;

        const highp vec3 W = vec3(0.2125, 0.7154, 0.0721);

        void main()
        {
            lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
            float luminance = dot(textureColor.rgb, W);

            gl_FragColor = vec4(vec3(luminance), textureColor.a);
        }
);
namespace ben{
    namespace ngp{
        class GPUImageGrayscaleFilter:public GPUImageFilter {
        public:
            GPUImageGrayscaleFilter();

            GPUImageGrayscaleFilter(JNIEnv *env);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;
        };
    }
}

#endif //NATIVEGPUIMAGE_GPU_IMAGE_GRAYSCALE_FILTER_HPP
