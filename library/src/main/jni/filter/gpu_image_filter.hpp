//
// Created by ben622 on 2019/9/16.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_FILTER_HPP

#include "../include/jni/JniHelpers.h"
#include <vector>
#include <pthread.h>

using namespace ben::jni;
using namespace std;

enum GL_DRAW_TYPE {
    DRAW_INTEGER,
    DRAW_FLOAT,
    DRAW_FLOAT_VEC2,
    DRAW_FLOAT_VEC3,
    DRAW_FLOAT_VEC4,
    DRAW_FLOAT_ARRAY,
    DRAW_POINT,
    DRAW_UNIFORM_MATRIX3F,
    DRAW_UNIFORM_MATRIX4F


};
typedef struct runOnDrawArgs {
    int location;
    int intValue;
    float floatValue;
    float *arrayValuePtr;
    int arrayValueLength;
    float x;
    float y;
    GL_DRAW_TYPE glDrawType;
    void *filter; //link ben::ngp::GPUImageFilter
    pthread_t *pthread;
} GL_VARS;

static char *NO_FILTER_VERTEX_SHADER = "attribute vec4 position;"\
                                             "attribute vec4 inputTextureCoordinate;"\
                                             ""\
                                             "varying vec2 textureCoordinate;"\
                                             ""\
                                             "void main()"\
                                             "{"\
                                             "    gl_Position = position;"\
                                             "    textureCoordinate = inputTextureCoordinate.xy;"\
                                             "}";

static char *NO_FILTER_FRAGMENT_SHADER = "varying highp vec2 textureCoordinate;"\
                                               " "\
                                               "uniform sampler2D inputImageTexture;"\
                                               " "\
                                               "void main()"\
                                               "{"\
                                               "     gl_FragColor = texture2D(inputImageTexture, textureCoordinate);"\
                                               "}";
/*
#define GET_STR(x) #x

static const char *NO_FILTER_VERTEX_SHADER = GET_STR(
        attribute vec4 position;
        attribute vec4 inputTextureCoordinate;

        varying vec2 textureCoordinate;

        void main()
        {
            gl_Position = position;
            textureCoordinate = inputTextureCoordinate.xy;
        }
);
static const char *NO_FILTER_FRAGMENT_SHADER = GET_STR(
        varying highp vec2 textureCoordinate;

        uniform sampler2D inputImageTexture;

        void main()
        {
            gl_FragColor = texture2D(inputImageTexture, textureCoordinate);
        }
);*/
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
            bool isInitialized = false;


        private:
            ANativeWindow *nativeWindow;
            EGLDisplay *eglDisplay;
            EGLSurface *eglSurface;

        private:
            vector<GL_VARS *> runOnDrawGLVars;
            vector<pthread_t *> runOnDrawThreads;
            //互斥锁
            pthread_mutex_t runOnDrawMutex;
            //互斥锁条件变量
            pthread_cond_t runOndrawMutexCondition;

        public:
            //filter api
            GPUImageFilter();

            GPUImageFilter(char *vertexShader, char *fragmentShader);

            ~GPUImageFilter() {}

            virtual void onOutputSizeChanged(int width, int height);

            virtual void onInit();

            virtual void onInitialized();

            virtual void onDestory();

            virtual void
            onDraw(int textureId, const void *cubeBufferPtr, const void *textureBufferPtr);

            void destory();

            void onDrawArraysPre();

            void ifNeedInit();

        public:

            //register jni api
            GPUImageFilter(JNIEnv *env) {

            };

            virtual void initialize(JNIEnv *env) {

            };

            virtual void mapFields() {

            };

            virtual const char *getCanonicalName() const {
                return "";
            };


            //////////////////run on draw////////////////
            void addDrawThread(GL_VARS *glVars);

            void setInteger(int location, int intValue);

            void setFloat(int location, float floatValue);

            void setFloatVec2(int location, float *arrayValuePtr);

            void setFloatVec3(int location, float *arrayValuePtr);

            void setFloatVec4(int location, float *arrayValuePtr);

            void setFloatArray(int location, float *arrayValuePtr, int arrayValueLength);

            void setPoint(int location, float x, float y);

            void setUniformMatrix3f(int location, float *arrayValuePtr);

            void setUniformMatrix4f(int location, float *arrayValuePtr);

            void runPendingOnDrawTasks();

            ////////////////////getter and setter/////////////////////////
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

            ANativeWindow *getNativeWindow() const;

            void setNativeWindow(ANativeWindow *nativeWindow);

            EGLDisplay *getEglDisplay() const;

            void setEglDisplay(EGLDisplay *eglDisplay);

            EGLSurface *getEglSurface() const;

            void setEglSurface(EGLSurface *eglSurface);

        };
    }
}


#endif //NATIVEGPUIMAGE_GPU_IMAGE_FILTER_HPP
