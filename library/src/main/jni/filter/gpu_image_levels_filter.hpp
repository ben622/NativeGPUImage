//
// Created by ben622 on 2019/10/8.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_LEVELS_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_LEVELS_FILTER_HPP

#include "gpu_image_filter.hpp"

#define JAVA_LEVELS_FILTER "com/ben/android/library/filter/GPUImageLevelsFilter"

static char *LEVELS_FRAGMET_SHADER = GET_STR(
        varying
                highp
        vec2 textureCoordinate;

        uniform
        sampler2D inputImageTexture;
        uniform
                mediump
        vec3 levelMinimum;
        uniform
                mediump
        vec3 levelMiddle;
        uniform
                mediump
        vec3 levelMaximum;
        uniform
                mediump
        vec3 minOutput;
        uniform
                mediump
        vec3 maxOutput;

        void main() {
            mediump
            vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

            gl_FragColor = vec4(mix(minOutput, maxOutput,
                                    pow(min(max(textureColor.rgb - levelMinimum, vec3(0.0)) /
                                            (levelMaximum - levelMinimum), vec3(1.0)),
                                        1.0 / levelMiddle)), textureColor.a);
        }
);

namespace ben {
    namespace ngp {
        class GPUImageLevelsFilter : public GPUImageFilter {
        private:
            int minLocation;
            float *min;
            int midLocation;
            float *mid;
            int maxLocation;
            float *max;
            int minOutputLocation;
            float *minOutput;
            int maxOutputLocation;
            float *maxOutput;
            //jni
            float minV1 = 0.0f;
            float minV2 = 0.0f;
            float minV3 = 0.0f;
            float midV1 = 1.0f;
            float midV2 = 1.0f;
            float midV3 = 1.0f;
            float maxV1 = 1.0f;
            float maxV2 = 1.0f;
            float maxV3 = 1.0f;
            float minOutputV1 = 0.0f;
            float minOutputV2 = 0.0f;
            float minOutputV3 = 0.0f;
            float maxOutputV1 = 1.0f;
            float maxOutputV2 = 1.0f;
            float maxOutputV3 = 1.0f;

            float nMin = 0.0f;
            float nMid = 0.2f;
            float nMax = 1.0f;
            float nMinOut = 0.0f;
            float nMaxOut = 1.0f;
        public:
            GPUImageLevelsFilter();

            GPUImageLevelsFilter(JNIEnv *env);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            virtual void onInit();

            virtual void onInitialized();

            void updateUniforms();

            void setMin(float min, float mid, float max, float minOut, float maxOut);

            void setMin(float min, float mid, float max);

            void setRedMin(float min, float mid, float max, float minOut, float maxOut);

            void setRedMin(float min, float mid, float max);

            void setGreenMin(float min, float mid, float max, float minOut, float maxOut);

            void setGreenMin(float min, float mid, float max);

            void setBlueMin(float min, float mid, float max, float minOut, float maxOut);

            void setBlueMin(float min, float mid, float max);
        };
    }
}

#endif //NATIVEGPUIMAGE_GPU_IMAGE_LEVELS_FILTER_HPP
