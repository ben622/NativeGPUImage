//
// Created by ben622 on 2019/9/16.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_FILTER_HPP

#include "../include/jni/JniHelpers.h"
#include "../include/queue.h"
#include "../util/filter_tools.hpp"
#include "../util/rotation.hpp"
#include "../util/open_gl_util.hpp"
#include "../util/textur_rotation_util.hpp"
#include <cstring>
#include <vector>
#include <pthread.h>

using namespace ben::jni;
using namespace std;

typedef void (*CALLBACK)(void *);

enum GL_DRAW_TYPE {
    DRAW_INTEGER,
    DRAW_FLOAT,
    DRAW_FLOAT_VEC2,
    DRAW_FLOAT_VEC3,
    DRAW_FLOAT_VEC4,
    DRAW_FLOAT_ARRAY,
    DRAW_POINT,
    DRAW_UNIFORM_MATRIX3F,
    DRAW_UNIFORM_MATRIX4F,
    DRAW_CALLBACK,
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
    CALLBACK callback;
    void *callbackArg;
} GL_VARS;

#define GET_STR(x) #x

static char *NO_FILTER_VERTEX_SHADER = GET_STR(
        attribute
        vec4 position;
        attribute
        vec4 inputTextureCoordinate;
        varying
        vec2 textureCoordinate;
        void main() {
            gl_Position = position;
            textureCoordinate = inputTextureCoordinate.xy;
        }
);
static char *NO_FILTER_FRAGMENT_SHADER = GET_STR(
        varying
        highp
        vec2 textureCoordinate;
        uniform
        sampler2D inputImageTexture;
        void main() {
            gl_FragColor = texture2D(inputImageTexture, textureCoordinate);
        }
);
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
            bool isFilterInitialized = false;
            bool isFBO = false;

        private:
            ANativeWindow *nativeWindow;
            EGLDisplay *eglDisplay;
            EGLSurface *eglSurface;
        private:
            vector<GL_VARS *> runOnDrawGLVars;
        public:
            //register jni api
            GPUImageFilter(JNIEnv *env) : JavaClass(env) {
                this->vertexShader = NO_FILTER_VERTEX_SHADER;
                this->fragmentShader = NO_FILTER_FRAGMENT_SHADER;
            };

            virtual void initialize(JNIEnv *env) {
                LOGI("register native filter > %s", this->getCanonicalName());
                setClass(env);
            };

            virtual void mapFields() {
            };

            virtual const char *getCanonicalName() const {
                return NULL;
            };

        public:
            //filter api
            GPUImageFilter();

            GPUImageFilter(char *vertexShader, char *fragmentShader);

            GPUImageFilter(char *vertexShader, char *fragmentShader, JNIEnv *env);

            ~GPUImageFilter() {}

            virtual void onOutputSizeChanged(int width, int height);

            virtual void onInit();

            virtual void onInitialized();

            virtual void onDestory();


            virtual void
            onDraw(int textureId, float *cubeBufferPtr, float *textureBufferPtr);

            void destory();

            virtual void onDrawArraysPre();

            virtual void onDrawPre();

            void ifNeedInit();

        public:

            //////////////////run on draw////////////////
            void addDrawThread(GL_VARS *glVars);

            void addDrawThread(CALLBACK callback,void* callbackArg);

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

            void run(GL_VARS *glVars);

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

            bool isIsFilterInitialized() const;

            void setIsFilterInitialized(bool isFilterInitialized);

            ANativeWindow *getNativeWindow() const;

            void setNativeWindow(ANativeWindow *nativeWindow);

            EGLDisplay *getEglDisplay() const;

            void setEglDisplay(EGLDisplay *eglDisplay);

            EGLSurface *getEglSurface() const;

            void setEglSurface(EGLSurface *eglSurface);

            bool isIsFBO() const;

            void setIsFBO(bool isFBO);

        };
    }
}


#endif //NATIVEGPUIMAGE_GPU_IMAGE_FILTER_HPP
