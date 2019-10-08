//
// Created by ben622 on 2019/10/8.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_RGB_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_RGB_FILTER_HPP

#include "gpu_image_filter.hpp"
#define JAVA_RGB_FILTER "com/ben/android/library/filter/GPUImageRGBFilter"
static char *RGB_FRAGMENT_SHADER = GET_STR(
        varying highp vec2 textureCoordinate;

        uniform sampler2D inputImageTexture;
        uniform highp float red;
        uniform highp float green;
        uniform highp float blue;

        void main()
        {
            highp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

            gl_FragColor = vec4(textureColor.r * red, textureColor.g * green, textureColor.b * blue, 1.0);
        }
);
namespace ben{
    namespace ngp{
        class GPUImageRGBFilter:public GPUImageFilter{
        private:
            int redLocation;
            float red;
            int greenLocation;
            float green;
            int blueLocation;
            float blue;
        public:
            GPUImageRGBFilter();

            GPUImageRGBFilter(JNIEnv *env);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            virtual void onInit();

            virtual void onInitialized();

            void setRed(float red);

            void setGreen(float green);

            void setBlue(float blue);
        };
    }
}

#endif //NATIVEGPUIMAGE_GPU_IMAGE_RGB_FILTER_HPP
