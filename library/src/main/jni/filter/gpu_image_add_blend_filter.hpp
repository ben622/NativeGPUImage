//
// Created by ben622 on 2019/9/28.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_ADD_BLEND_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_ADD_BLEND_FILTER_HPP

#include "gpu_image_two_input_filter.hpp"
#define JAVA_ADD_BLEND_FILTER "com/ben/android/library/filter/GPUImageAddBlendFilter"

static char *ADD_BLEND_FRAGMENT_SHADER = GET_STR(
        varying
        highp
        vec2 textureCoordinate;
        varying
        highp
        vec2 textureCoordinate2;

        uniform
        sampler2D inputImageTexture;
        uniform
        sampler2D inputImageTexture2;

        void main() {
            lowp
            vec4 base = texture2D(inputImageTexture, textureCoordinate);
            lowp
            vec4 overlay = texture2D(inputImageTexture2, textureCoordinate2);

            mediump float r;
            if (overlay.r * base.a + base.r * overlay.a >= overlay.a * base.a) {
                r = overlay.a * base.a + overlay.r * (1.0 - base.a) + base.r * (1.0 - overlay.a);
            } else {
                r = overlay.r + base.r;
            }

            mediump float g;
            if (overlay.g * base.a + base.g * overlay.a >= overlay.a * base.a) {
                g = overlay.a * base.a + overlay.g * (1.0 - base.a) + base.g * (1.0 - overlay.a);
            } else {
                g = overlay.g + base.g;
            }

            mediump float b;
            if (overlay.b * base.a + base.b * overlay.a >= overlay.a * base.a) {
                b = overlay.a * base.a + overlay.b * (1.0 - base.a) + base.b * (1.0 - overlay.a);
            } else {
                b = overlay.b + base.b;
            }

            mediump float a = overlay.a + base.a - overlay.a * base.a;

            gl_FragColor = vec4(r, g, b, a);
        }
);
namespace ben {
    namespace ngp {
        class GPUImageAddBlendFilter : public GPUImageTwoInputFilter {
        public:
            GPUImageAddBlendFilter();

            GPUImageAddBlendFilter(JNIEnv *env);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_ADD_BLEND_FILTER_HPP