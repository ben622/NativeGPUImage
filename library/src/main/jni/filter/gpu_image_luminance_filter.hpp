//
// Created by ben622 on 2019/10/8.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_LUMINANCE_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_LUMINANCE_FILTER_HPP

#include "gpu_image_filter.hpp"
#define JAVA_LUMINANCE_FILTER "com/ben/android/library/filter/GPUImageLuminanceFilter"
static char *LUMINANCE_FRAGMENT_SHADER = GET_STR(
        precision highp float;

        varying vec2 textureCoordinate;

        uniform sampler2D inputImageTexture;

// Values from \Graphics Shaders: Theory and Practice\ by Bailey and Cunningham
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
        class GPUImageLuminanceFilter:public GPUImageFilter{
        public:
            GPUImageLuminanceFilter(JNIEnv *env);

            const char *getCanonicalName() const override;
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_LUMINANCE_FILTER_HPP
