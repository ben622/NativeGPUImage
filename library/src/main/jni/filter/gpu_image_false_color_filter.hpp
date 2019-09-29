//
// Created by ben622 on 2019/9/29.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_FALSE_COLOR_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_FALSE_COLOR_FILTER_HPP

#include "gpu_image_filter.hpp"

#define JAVA_FALSE_COLOR_FILTER "com/ben/android/library/filter/GPUImageFalseColorFilter"
static char *FALSECOLOR_FRAGMENT_SHADER = GET_STR(
        precision
        lowp float;

        varying
        highp
        vec2 textureCoordinate;

        uniform
        sampler2D inputImageTexture;
        uniform float intensity;
        uniform
        vec3 firstColor;
        uniform
        vec3 secondColor;

        const mediump vec3
        luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);

        void main() {
            lowp
            vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
            float luminance = dot(textureColor.rgb, luminanceWeighting);

            gl_FragColor = vec4(mix(firstColor.rgb, secondColor.rgb, luminance), textureColor.a);
        }
);
namespace ben {
    namespace ngp {
        class GPUImageFalseColorFilter : public GPUImageFilter {
        private:
            int secondColorLocation;
            int firstColorLocation;

            float firstRed = 0.0f;
            float firstGreen = 0.0f;
            float firstBlue = 0.5f;
            float secondRed = 1.0f;
            float secondGreen = 0.0f;
            float secondBlue = 0.0f;

            float *firstColor;
            float *secondColor;
        public:
            GPUImageFalseColorFilter();

            GPUImageFalseColorFilter(JNIEnv *env);

        public:
            virtual void onInit();

            virtual void onInitialized();

        public:
            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

        public:
            void setFirstColor(float *firstColor);

            void setSecondColor(float *secondColor);

        };
    }
}

#endif //NATIVEGPUIMAGE_GPU_IMAGE_FALSE_COLOR_FILTER_HPP
