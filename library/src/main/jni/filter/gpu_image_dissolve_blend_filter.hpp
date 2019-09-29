//
// Created by ben622 on 2019/9/29.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_DISSOLVE_BLEND_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_DISSOLVE_BLEND_FILTER_HPP

#include "gpu_image_mix_blend_filter.hpp"
#define JAVA_DISSOLVE_BLEND_FILTER "com/ben/android/library/filter/GPUImageDissolveBlendFilter"
static char *DISSOLVE_BLEND_FRAGMENT_SHADER = GET_STR(
        varying highp vec2 textureCoordinate;
        varying highp vec2 textureCoordinate2;

        uniform sampler2D inputImageTexture;
        uniform sampler2D inputImageTexture2;
        uniform lowp float mixturePercent;

        void main()
        {
            lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
            lowp vec4 textureColor2 = texture2D(inputImageTexture2, textureCoordinate2);

            gl_FragColor = mix(textureColor, textureColor2, mixturePercent);
        }
);
namespace ben{
    namespace ngp{
        class GPUImageDissolveBlendFilter:public GPUImageMixBlendFilter {
        public:
            GPUImageDissolveBlendFilter(JNIEnv *env);
            GPUImageDissolveBlendFilter(float mix,JNIEnv *env);
        public:
            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_DISSOLVE_BLEND_FILTER_HPP
