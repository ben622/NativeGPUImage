//
// Created by ben622 on 2019/10/8.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_BRIGHTNESS_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_BRIGHTNESS_FILTER_HPP

#include "gpu_image_filter.hpp"
#define JAVA_BRIGHTNESS_FILTER "com/ben/android/library/filter/GPUImageBrightnessFilter"
static char *BRIGHTNESS_FRAGMENT_SHADER = GET_STR(
        varying highp vec2 textureCoordinate;

        uniform sampler2D inputImageTexture;
        uniform lowp float brightness;

        void main()
        {
            lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

            gl_FragColor = vec4((textureColor.rgb + vec3(brightness)), textureColor.w);
        }
);

namespace ben{
    namespace ngp{
        class GPUImageBrightnessFilter:public GPUImageFilter{
        private:
            int brightnessLocation;
            float brightness;
        public:
            GPUImageBrightnessFilter();

            GPUImageBrightnessFilter(JNIEnv *env);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            virtual void onInit();

            virtual void onInitialized();

            void setBrightness(float brightness);

            float getBrightness() const;
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_BRIGHTNESS_FILTER_HPP
