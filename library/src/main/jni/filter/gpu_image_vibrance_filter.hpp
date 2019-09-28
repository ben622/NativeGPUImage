//
// Created by ben622 on 2019/9/28.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_VIBRANCE_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_VIBRANCE_FILTER_HPP

#include "gpu_image_filter.hpp"

#define JAVA_VIBRANCE_FILTER "com/ben/android/library/filter/GPUImageVibranceFilter"

static char *VIBRANCE_FRAGMENT_SHADER = GET_STR(
        varying
        highp
        vec2 textureCoordinate;

        uniform
        sampler2D inputImageTexture;
        uniform
        lowp float vibrance;

        void main() {
            lowp
            vec4 color = texture2D(inputImageTexture, textureCoordinate);
            lowp float average = (color.r + color.g + color.b) / 3.0;
            lowp float mx = max(color.r, max(color.g, color.b));
            lowp float amt = (mx - average) * (-vibrance * 3.0);
            color.rgb = mix(color.rgb, vec3(mx), amt);
            gl_FragColor = color;
        }
);
namespace ben {
    namespace ngp {
        class GPUImageVibranceFilter : public GPUImageFilter {
        private:
            int vibranceLocation;
            float vibrance;
        public:
            GPUImageVibranceFilter();

            GPUImageVibranceFilter(JNIEnv *env);

            virtual void onInit();

            virtual void onInitialized();

        public:
            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            void setVibrance(float vibrance);
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_VIBRANCE_FILTER_HPP
