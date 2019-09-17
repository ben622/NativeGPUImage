//
// Created by ben622 on 2019/9/17.
//

#include "gpu_image_render.hpp"
#include "include/jni/JniHelpers.h"
#include <android/native_window_jni.h>
#include "util/jni_util.hpp"
#include "util/open_gl_util.hpp"
#include "util/textur_rotation_util.hpp"

using namespace ben::util;

static void onDrawFrame(ben::ngp::GPUImageRender* render){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //runAll(runOnDraw);
    render->getFilter().onDraw(render->getGlTextureId(), render->getGlCubeBuffer(), render->getGlTextureBuffer());
    //runAll(runOnDrawEnd);
    /*if (surfaceTexture != null) {
        surfaceTexture.updateTexImage();
    }*/
}

static void nativeSurfaceCreated(JNIEnv *env, jobject javaThis, jobject surface,jobject jbitmap,int width,int height) {
    //1.准备opengl环境
    ANativeWindow *nativeWindow = ANativeWindow_fromSurface(env, surface);
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) {
        LOGE("%s", "get display failed!");
        return;
    }
    if (EGL_TRUE != eglInitialize(display, 0, 0)) {
        LOGE("%s", "eglInitialize failed!");
        return;
    }
    //surface 配置
    //输出配置
    EGLConfig config;
    EGLint configNum;
    //输入配置
    EGLint configSpec[] = {
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_SURFACE_TYPE,
            EGL_WINDOW_BIT,
            EGL_NONE
    };

    if (EGL_TRUE != eglChooseConfig(display, configSpec, &config, 1, &configNum)) {
        LOGE("%s", "eglChooseConfig failed!");
        return;
    }
    //创建surface （关联原始窗口）
    EGLSurface winSurface = eglCreateWindowSurface(display, config, nativeWindow, 0);

    if (winSurface == EGL_NO_SURFACE) {
        LOGE("%s", "eglCreateWindowSurface failed!");
        return;
    }
    //创建关联上下文
    const EGLint ctxAttr[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
    };
    EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxAttr);
    if (context == EGL_NO_CONTEXT) {
        LOGE("%s", "eglCreateContext failed!");
        return;
    }
    //egl 关联 openl
    if (EGL_TRUE != eglMakeCurrent(display, winSurface, winSurface, context)) {
        LOGE("%s", "eglMakeCurrent failed!");
        return;
    }
    LOGE("%s", "EGL Init Success!");


    //2.初始化GPUImageRender
    float backgroundRed = 0;
    float backgroundGreen = 0;
    float backgroundBlue = 0;
    glClearColor(backgroundRed, backgroundGreen, backgroundBlue, 1);
    glDisable(GL_DEPTH_TEST);
    //初始化默认filter
    ben::ngp::GPUImageRender* render = getNativeRenderInstance(env, javaThis);
    render->setIsPreparGLEnvironment(JNI_TRUE);
    render->setFilter(*new ben::ngp::GPUImageFilter());
    render->getFilter().ifNeedInit();

    //create texu
    render->setGlTextureId(
            loadTextureByBitmap(env, jbitmap, width, height, render->getGlTextureId()));
    render->setImageWidth(width);
    render->setImageHeight(height);

    //run
    onDrawFrame(render);
}

static void nativeSurfaceChanged(JNIEnv *env, jobject javaThis, jint width, jint height) {
    ben::ngp::GPUImageRender* render = getNativeRenderInstance(env, javaThis);
    if (!render->isIsPreparGLEnvironment()) {
        LOGE("%s", "opengl environment is not ready!");
        return;
    }
    render->setOutputWidth(width);
    render->setOutputHeight(height);

    glViewport(0, 0, width, height);
    glUseProgram(render->getFilter().getGlProgId());
    //call filter onOutputSizeChanged
    render->getFilter().onOutputSizeChanged(width, height);

    /*adjustImageScaling();
    synchronized (surfaceChangedWaiter) {
        surfaceChangedWaiter.notifyAll();
    }*/
}



ben::ngp::GPUImageRender::GPUImageRender() : NativeObject() {

}

ben::ngp::GPUImageRender::GPUImageRender(ben::ngp::GPUImageFilter filter) {
    this->filter = filter;
}

ben::ngp::GPUImageRender::GPUImageRender(JNIEnv *env) : NativeObject(env) {
    initialize(env);
}

ben::ngp::GPUImageRender::~GPUImageRender() {

}

void ben::ngp::GPUImageRender::initialize(JNIEnv *env) {

    glCubeBuffer = CUBE;
    glTextureBuffer = TEXTURE_NO_ROTATION;

    addNativeMethod("nativeSurfaceCreated", (void *) nativeSurfaceCreated, kTypeVoid,
                    "Landroid/view/Surface;","Landroid/graphics/Bitmap;",kTypeInt,kTypeInt, NULL);
    addNativeMethod("nativeSurfaceChanged", (void *) nativeSurfaceChanged, kTypeVoid,
                    kTypeInt, kTypeInt, NULL);
    registerNativeMethods(env);
}

void ben::ngp::GPUImageRender::mapFields() {

}

const char *ben::ngp::GPUImageRender::getCanonicalName() const {
    return "com/ben/android/library/GPUImageRender";
}

ben::ngp::GPUImageFilter &ben::ngp::GPUImageRender::getFilter() {
    return filter;
}

void ben::ngp::GPUImageRender::setFilter(ben::ngp::GPUImageFilter &filter) {
    GPUImageRender::filter = filter;
}

int ben::ngp::GPUImageRender::getOutputWidth() const {
    return outputWidth;
}

void ben::ngp::GPUImageRender::setOutputWidth(int outputWidth) {
    GPUImageRender::outputWidth = outputWidth;
}

int ben::ngp::GPUImageRender::getOutputHeight() const {
    return outputHeight;
}

void ben::ngp::GPUImageRender::setOutputHeight(int outputHeight) {
    GPUImageRender::outputHeight = outputHeight;
}

int ben::ngp::GPUImageRender::getImageWidth() const {
    return imageWidth;
}

void ben::ngp::GPUImageRender::setImageWidth(int imageWidth) {
    GPUImageRender::imageWidth = imageWidth;
}

int ben::ngp::GPUImageRender::getImageHeight() const {
    return imageHeight;
}

void ben::ngp::GPUImageRender::setImageHeight(int imageHeight) {
    GPUImageRender::imageHeight = imageHeight;
}

bool ben::ngp::GPUImageRender::isIsPreparGLEnvironment() const {
    return isPreparGLEnvironment;
}

void ben::ngp::GPUImageRender::setIsPreparGLEnvironment(bool isPreparGLEnvironment) {
    GPUImageRender::isPreparGLEnvironment = isPreparGLEnvironment;
}

int ben::ngp::GPUImageRender::getGlTextureId() const {
    return glTextureId;
}

void ben::ngp::GPUImageRender::setGlTextureId(int glTextureId) {
    GPUImageRender::glTextureId = glTextureId;
}

float *ben::ngp::GPUImageRender::getGlCubeBuffer() const {
    return glCubeBuffer;
}

void ben::ngp::GPUImageRender::setGlCubeBuffer(float *glCubeBuffer) {
    GPUImageRender::glCubeBuffer = glCubeBuffer;
}

float *ben::ngp::GPUImageRender::getGlTextureBuffer() const {
    return glTextureBuffer;
}

void ben::ngp::GPUImageRender::setGlTextureBuffer(float *glTextureBuffer) {
    GPUImageRender::glTextureBuffer = glTextureBuffer;
}

int *ben::ngp::GPUImageRender::getGlRgbBuffer() const {
    return glRgbBuffer;
}

void ben::ngp::GPUImageRender::setGlRgbBuffer(int *glRgbBuffer) {
    GPUImageRender::glRgbBuffer = glRgbBuffer;
}


