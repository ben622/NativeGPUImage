//
// Created by ben622 on 2019/9/17.
//
#ifndef NATIVEGPUIMAGE_GPU_IMAGE_RENDER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_RENDER_HPP

#include "include/jni/JniHelpers.h"
#include "filter/gpu_image_filter.hpp"
#include "util/rotation.hpp"
#include "util/scale_type.hpp"
#include "util/textur_rotation_util.hpp"
#include "filter/gpu_image_filter_group.hpp"

#define NO_IMAGE  -1
using namespace ben::jni;
using namespace ben::util;
namespace ben {
    namespace ngp {
        class GPUImageRender : public JavaClass {
        private:
            GPUImageFilter* filter;
            int outputWidth;
            int outputHeight;
            int imageWidth;
            int imageHeight;

            int glTextureId = NO_IMAGE;
            float *glCubeBuffer;
            float *glTextureBuffer;
            int *glRgbBuffer;

            float backgroundRed = 0;
            float backgroundGreen = 0;
            float backgroundBlue = 0;

            Rotation rotation;
            bool flipHorizontal;
            bool flipVertical;
            ScaleType scaleType = ScaleType::CENTER_INSIDE;


            bool isPreparGLEnvironment; //opengl 环境是否准备就绪
        public:
            void resetFilter(GPUImageFilter *filter);

            void renderBitmap(JNIEnv *env,jobject jbitmap);

            void surfaceChange(int width, int height);

            void reqeustRender();
        public:
            GPUImageRender();

            GPUImageRender(GPUImageFilter* filter);

            GPUImageRender(JNIEnv *env);

            void adjustImageScaling();

            float addDistance(float coordinate, float distance);
            virtual ~GPUImageRender();

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            GPUImageFilter *getFilter() const;

            void setFilter(GPUImageFilter *filter);

            int getOutputWidth() const;

            void setOutputWidth(int outputWidth);

            int getOutputHeight() const;

            void setOutputHeight(int outputHeight);

            int getImageWidth() const;

            void setImageWidth(int imageWidth);

            int getImageHeight() const;

            void setImageHeight(int imageHeight);

            bool isIsPreparGLEnvironment() const;

            void setIsPreparGLEnvironment(bool isPreparGLEnvironment);

            int getGlTextureId() const;

            void setGlTextureId(int glTextureId);

            int *getGlRgbBuffer() const;

            void setGlRgbBuffer(int *glRgbBuffer);

            float getBackgroundRed() const;

            void setBackgroundRed(float backgroundRed);

            float getBackgroundGreen() const;

            void setBackgroundGreen(float backgroundGreen);

            float getBackgroundBlue() const;

            void setBackgroundBlue(float backgroundBlue);

            bool isFlipHorizontal() const;

            void setFlipHorizontal(bool flipHorizontal);

            bool isFlipVertical() const;

            void setFlipVertical(bool flipVertical);

            ScaleType getScaleType() const;

            void setScaleType(ScaleType scaleType);

            Rotation getRotation() const;

            void setRotation(Rotation rotation,
                             bool flipHorizontal, bool flipVertical);

            void setRotation(Rotation rotation);

            float *getGlCubeBuffer() const;

            float *getGlTextureBuffer() const;
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_RENDER_HPP
