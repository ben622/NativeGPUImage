//
// Created by ben622 on 2019/9/27.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_VIGNETTE_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_VIGNETTE_FILTER_HPP
#include "gpu_image_filter.hpp"
#define JAVA_VIGNETTE_FILTER "com/ben/android/library/filter/GPUImageVignetteFilter"

static char *VIGNETTING_FRAGMENT_SHADER = GET_STR(
        uniform sampler2D inputImageTexture;
        varying highp vec2 textureCoordinate;

        uniform lowp vec2 vignetteCenter;
        uniform lowp vec3 vignetteColor;
        uniform highp float vignetteStart;
        uniform highp float vignetteEnd;

        void main()
        {
            /*
            lowp vec3 rgb = texture2D(inputImageTexture, textureCoordinate).rgb;
            lowp float d = distance(textureCoordinate, vec2(0.5,0.5));
            rgb *= (1.0 - smoothstep(vignetteStart, vignetteEnd, d));
            gl_FragColor = vec4(vec3(rgb),1.0);
             */

            lowp vec3 rgb = texture2D(inputImageTexture, textureCoordinate).rgb;
            lowp float d = distance(textureCoordinate, vec2(vignetteCenter.x, vignetteCenter.y));
            lowp float percent = smoothstep(vignetteStart, vignetteEnd, d);
            gl_FragColor = vec4(mix(rgb.x, vignetteColor.x, percent), mix(rgb.y, vignetteColor.y, percent), mix(rgb.z, vignetteColor.z, percent), 1.0);
        }
);
namespace ben{
    namespace ngp{
        class GPUImageVignetteFilter:public GPUImageFilter{
        private:
             int vignetteCenterLocation;
            float vignetteCenterX;
            float vignetteCenterY;
            int vignetteColorLocation;
            float *vignetteColor;
            int vignetteStartLocation;
            float vignetteStart;
            int vignetteEndLocation;
            float vignetteEnd;

        public:
            GPUImageVignetteFilter();

            GPUImageVignetteFilter(JNIEnv *env);

            GPUImageVignetteFilter(char *vertexShader, char *fragmentShader, JNIEnv *env);

            GPUImageVignetteFilter(float vignetteCenterX,
                                   float vignetteCenterY, float *vignetteColor, float vignetteStart,
                                   float vignetteEnd);

        public:
            void initialize(JNIEnv *env) override;

            void mapFields() override;

            const char *getCanonicalName() const override;

        public:
            virtual void onInit();

            virtual void onInitialized();

        public:
            void setVignetteCenter(float vignetteCenterX,float vignetteCenterY);

            void setVignetteColor(float *vignetteColor);

            void setVignetteStart(float vignetteStart);

            void setVignetteEnd(float vignetteEnd);
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_VIGNETTE_FILTER_HPP
