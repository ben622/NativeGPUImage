//
// Created by ben622 on 2019/10/8.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_HAZE_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_HAZE_FILTER_HPP

#include "gpu_image_filter.hpp"
#include "../include/jni/JniHelpersCommon.h"

#define JAVA_HAZE_FILTER "com/ben/android/library/filter/GPUImageHazeFilter"
static char *HAZE_FRAGMENT_SHADER = GET_STR(
        varying highp vec2 textureCoordinate;

        uniform sampler2D inputImageTexture;

        uniform lowp float distance;
        uniform highp float slope;

        void main()
        {
            //todo reconsider precision modifiers
            highp vec4 color = vec4(1.0);//todo reimplement as a parameter

            highp float  d = textureCoordinate.y * slope  +  distance;

            highp vec4 c = texture2D(inputImageTexture, textureCoordinate) ; // consider using unpremultiply

            c = (c - d * color) / (1.0 -d);

            gl_FragColor = c; //consider using premultiply(c);
        }
);
namespace ben{
    namespace ngp{
        class GPUImageHazeFilter:public GPUImageFilter{
        private:
            float distance;
            int distanceLocation;
            float slope;
            int slopeLocation;
        public:
            GPUImageHazeFilter();

            GPUImageHazeFilter(JNIEnv *env);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            virtual void onInit();

            virtual void onInitialized();

            void setDistance(float distance);

            void setSlope(float slope);
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_HAZE_FILTER_HPP
