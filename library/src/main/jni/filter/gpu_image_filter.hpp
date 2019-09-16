//
// Created by ben622 on 2019/9/16.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_FILTER_HPP

#include "../include/jni/JniHelpers.h"
#include <vector>
using namespace ben::jni;
static const char *NO_FILTER_VERTEX_SHADER = "attribute vec4 position;\n"
                                             "attribute vec4 inputTextureCoordinate;\n"
                                             " \n"
                                             "varying vec2 textureCoordinate;\n"
                                             " \n"
                                             "void main()\n"
                                             "{\n"
                                             "    gl_Position = position;\n"
                                             "    textureCoordinate = inputTextureCoordinate.xy;\n"
                                             "}";

static const char *NO_FILTER_FRAGMENT_SHADER = "varying highp vec2 textureCoordinate;\n"
                                               " \n"
                                               "uniform sampler2D inputImageTexture;\n"
                                               " \n"
                                               "void main()\n"
                                               "{\n"
                                               "     gl_FragColor = texture2D(inputImageTexture, textureCoordinate);\n"
                                               "}";
namespace ben {
    namespace ngp {
        class GPUImageFilter : public JavaClass {
        private:
            char *vertexShader;
            char *fragmentShader;
            int glProgId;
            int glAttribPosition;
            int glUniformTexture;
            int glAttribTextureCoordinate;
            int outputWidth;
            int outputHeight;
            bool isInitialized;

            //std::vector
        public:

            GPUImageFilter(JNIEnv *env) {

            };

            virtual void initialize(JNIEnv *env) {

            };

            virtual void mapFields() {

            };

            virtual const char *getCanonicalName() const {
                return "";
            };

            GPUImageFilter();

            GPUImageFilter(char *vertexShader, char *fragmentShader);

            ~GPUImageFilter() {}

            virtual void onOutputSizeChanged(int width, int height);

            virtual void destory();

            virtual void onInit();

            virtual void onInitialized();

            virtual void onDestory();

            virtual void
            onDraw(int textureId, const void *cubeBufferPtr, const void *textureBufferPtr);

            virtual void onDrawArraysPre();

            virtual void ifNeedInit();

            char *getVertexShader() const {
                return vertexShader;
            }

            void setVertexShader(char *vertexShader) {
                GPUImageFilter::vertexShader = vertexShader;
            }

            char *getFragmentShader() const {
                return fragmentShader;
            }

            void setFragmentShader(char *fragmentShader) {
                GPUImageFilter::fragmentShader = fragmentShader;
            }

            int getGlProgId() const {
                return glProgId;
            }

            void setGlProgId(int glProgId) {
                GPUImageFilter::glProgId = glProgId;
            }

            int getGlAttribPosition() const {
                return glAttribPosition;
            }

            void setGlAttribPosition(int glAttribPosition) {
                GPUImageFilter::glAttribPosition = glAttribPosition;
            }

            int getGlUniformTexture() const {
                return glUniformTexture;
            }

            void setGlUniformTexture(int glUniformTexture) {
                GPUImageFilter::glUniformTexture = glUniformTexture;
            }

            int getGlAttribTextureCoordinate() const {
                return glAttribTextureCoordinate;
            }

            void setGlAttribTextureCoordinate(int glAttribTextureCoordinate) {
                GPUImageFilter::glAttribTextureCoordinate = glAttribTextureCoordinate;
            }

            int getOutputWidth() const {
                return outputWidth;
            }

            void setOutputWidth(int outputWidth) {
                GPUImageFilter::outputWidth = outputWidth;
            }

            int getOutputHeight() const {
                return outputHeight;
            }

            void setOutputHeight(int outputHeight) {
                GPUImageFilter::outputHeight = outputHeight;
            }

            bool isIsInitialized() const {
                return isInitialized;
            }

            void setIsInitialized(bool isInitialized) {
                GPUImageFilter::isInitialized = isInitialized;
            }
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_FILTER_HPP
