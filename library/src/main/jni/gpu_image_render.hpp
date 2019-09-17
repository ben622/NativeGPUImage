//
// Created by ben622 on 2019/9/17.
//
#ifndef NATIVEGPUIMAGE_GPU_IMAGE_RENDER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_RENDER_HPP

#include "include/jni/JniHelpers.h"
#include "filter/gpu_image_filter.hpp"

#define NO_IMAGE  -1
static float CUBE[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f,
};

using namespace ben::jni;
namespace ben {
    namespace ngp {
        class GPUImageRender : public NativeObject {
        private:
            GPUImageFilter filter;
            int outputWidth;
            int outputHeight;
            int imageWidth;
            int imageHeight;

            int glTextureId = NO_IMAGE;
            float *glCubeBuffer;
            float *glTextureBuffer;
            int *glRgbBuffer;

            bool isPreparGLEnvironment; //opengl 环境是否准备就绪

        public:
            GPUImageRender();

            GPUImageRender(GPUImageFilter filter);

            GPUImageRender(JNIEnv *env);


            virtual ~GPUImageRender();

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            GPUImageFilter &getFilter();

            void setFilter(GPUImageFilter &filter);

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

            float *getGlCubeBuffer() const;

            void setGlCubeBuffer(float *glCubeBuffer);

            float *getGlTextureBuffer() const;

            void setGlTextureBuffer(float *glTextureBuffer);

            int *getGlRgbBuffer() const;

            void setGlRgbBuffer(int *glRgbBuffer);
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_RENDER_HPP
