//
// Created by ben622 on 2019/9/29.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_GAMMA_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_GAMMA_FILTER_HPP

#include "gpu_image_filter.hpp"
#define JAVA_GAMMA_FILTER "com/ben/android/library/filter/GPUImageGammaFilter"
static char *GAMMA_FRAGMENT_SHADER = GET_STR(
        varying
        highp
        vec2 textureCoordinate;

        uniform
        sampler2D inputImageTexture;
        uniform
        lowp float gamma;

        void main() {
            lowp
            vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

            gl_FragColor = vec4(pow(textureColor.rgb, vec3(gamma)), textureColor.w);
        }
);
namespace ben {
    namespace ngp {
        class GPUImageGammaFilter : public GPUImageFilter {
        private:
            int gammaLocation;
            float gamma;
        public:
            GPUImageGammaFilter();

            GPUImageGammaFilter(JNIEnv *env);

            virtual void onInit();

            virtual void onInitialized();

        public:
            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            void setGamma(float gamma);
        };
    }
}

#endif //NATIVEGPUIMAGE_GPU_IMAGE_GAMMA_FILTER_HPP
