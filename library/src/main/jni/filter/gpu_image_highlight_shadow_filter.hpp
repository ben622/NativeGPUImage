//
// Created by ben622 on 2019/10/8.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_HIGHLIGHT_SHADOW_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_HIGHLIGHT_SHADOW_FILTER_HPP

#include "gpu_image_filter.hpp"
#define JAVA_HIGHLIGHT_SHADOW_FILTER "com/ben/android/library/filter/GPUImageHighlightShadowFilter"

static char *HIGHLIGHT_SHADOW_FRAGMENT_SHADER = GET_STR(
        uniform sampler2D inputImageTexture;
        varying highp vec2 textureCoordinate;

        uniform lowp float shadows;
        uniform lowp float highlights;

        const mediump vec3 luminanceWeighting = vec3(0.3, 0.3, 0.3);

        void main()
        {
            lowp vec4 source = texture2D(inputImageTexture, textureCoordinate);
            mediump float luminance = dot(source.rgb, luminanceWeighting);

            mediump float shadow = clamp((pow(luminance, 1.0/(shadows+1.0)) + (-0.76)*pow(luminance, 2.0/(shadows+1.0))) - luminance, 0.0, 1.0);
            mediump float highlight = clamp((1.0 - (pow(1.0-luminance, 1.0/(2.0-highlights)) + (-0.8)*pow(1.0-luminance, 2.0/(2.0-highlights)))) - luminance, -1.0, 0.0);
            lowp vec3 result = vec3(0.0, 0.0, 0.0) + ((luminance + shadow + highlight) - 0.0) * ((source.rgb - vec3(0.0, 0.0, 0.0))/(luminance - 0.0));

            gl_FragColor = vec4(result.rgb, source.a);
        }
);

namespace ben{
    namespace ngp{
        class GPUImageHighlightShadowFilter:public GPUImageFilter{
        private:
            int shadowsLocation;
            float shadows;
            int highlightsLocation;
            float highlights;
        public:
            GPUImageHighlightShadowFilter();

            GPUImageHighlightShadowFilter(JNIEnv *env);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            virtual void onInit();

            virtual void onInitialized();

            void setShadows(float shadows);

            void setHighlights(float highlights);
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_HIGHLIGHT_SHADOW_FILTER_HPP
