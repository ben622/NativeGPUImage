//
// Created by ben622 on 2019/9/28.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_TWO_INPUT_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_TWO_INPUT_FILTER_HPP

#include "gpu_image_filter.hpp"
#define JAVA_TWO_INPUT_FILTER "com/ben/android/library/filter/GPUImageTwoInputFilter"

using namespace ben::util;
static char *TWO_INPUT_VERTEX_SHADER = GET_STR(
        attribute
        vec4 position;
        attribute
        vec4 inputTextureCoordinate;
        attribute
        vec4 inputTextureCoordinate2;

        varying
        vec2 textureCoordinate;
        varying
        vec2 textureCoordinate2;

        void main() {
            gl_Position = position;
            textureCoordinate = inputTextureCoordinate.xy;
            textureCoordinate2 = inputTextureCoordinate2.xy;
        }
);

namespace ben {
    namespace ngp {
        class GPUImageTwoInputFilter : public GPUImageFilter {
        private:
            int filterSecondTextureCoordinateAttribute;
            int filterInputTextureUniform2;
            int filterSourceTexture2 = NO_TEXTURE;
            float *texture2CoordinatesBuffer;
            jobject bitmap = NULL;
            void *pxiel = NULL;
            int bitmapWidth = 0;
            int bitmapHeight = 0;

        public:

            GPUImageTwoInputFilter(char *fragmentShader);
            GPUImageTwoInputFilter(char *fragmentShader,JNIEnv *env);
            GPUImageTwoInputFilter(char *vertexShader, char *fragmentShader, JNIEnv *env);

            virtual void setBitmap(jobject jbitmap);

            virtual void
            setRotation(ben::util::Rotation rotation, bool flipHorizontal, bool flipVertical);

            static void setBitmapCallback(void *filter);

        public:
            virtual void onInit();

            virtual void onInitialized();

            virtual void onDrawArraysPre();

            void onDestory() override;

        public:
            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

        public:
            void *getPxiel() const;

            void setPxiel(void *pxiel);

            int getBitmapWidth() const;

            void setBitmapWidth(int bitmapWidth);

            int getBitmapHeight() const;

            void setBitmapHeight(int bitmapHeight);

            const _jobject *getBitmap() const;
        };
    }
}

#endif //NATIVEGPUIMAGE_GPU_IMAGE_TWO_INPUT_FILTER_HPP
