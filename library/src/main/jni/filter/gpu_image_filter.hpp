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

enum GL_DRAW_TYPE{
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
    void *filter; //ben::ngp::GPUImageFilter
    pthread_t *pthread; //不需要主动创建线程，由GPUImageFilter创建
} GL_VARS;


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

            vector<GL_VARS *> runOnDrawGLVars;
            //互斥锁
            pthread_mutex_t runOnDrawMutex;
            //互斥锁条件变量
            pthread_cond_t runOndrawMutexCondition;

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

            //filter api
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

            //////////////////run on draw////////////////
            void addDrawThread(GL_VARS *glVars);

            void setInteger(int location, int intValue);

            void setFloat(int location, float floatValue);

            void setFloatVec2(int location, float *arrayValuePtr);

            void setFloatVec3(int location, float *arrayValuePtr);

            void setFloatVec4(int location, float *arrayValuePtr);

            void setFloatArray(int location, float *arrayValuePtr,int arrayValueLength);

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
        };
    }
}


#endif //NATIVEGPUIMAGE_GPU_IMAGE_FILTER_HPP
