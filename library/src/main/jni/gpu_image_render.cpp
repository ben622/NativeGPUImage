//
// Created by ben622 on 2019/9/17.
//

#include "gpu_image_render.hpp"
#include <android/native_window_jni.h>
#include "util/jni_util.hpp"
#include "util/open_gl_util.hpp"
#include <math.h>

#define MAX_FBO_SURFACE_WIDTH 5000
#define MAX_FBO_SURFACE_HEIGHT 5000

using namespace ben::util;

static EGLSurface winSurface;
static EGLContext context;
static EGLDisplay display;
static ANativeWindow *nativeWindow;

static EGLConfig eglConf;
static EGLSurface eglSurface;
static EGLContext eglCtx;
static EGLDisplay eglDisp;

void ben::ngp::GPUImageRender::nativeSurfaceCreated(JNIEnv *env, jclass javaThis, jobject surface) {
    //1.准备opengl环境
    nativeWindow = ANativeWindow_fromSurface(env, surface);
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) {
        LOGE("%s", "get eglDisplay failed!");
        return;
    }
    if (EGL_TRUE != eglInitialize(display, NULL, NULL)) {
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
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 16,
            EGL_STENCIL_SIZE, 0,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_SURFACE_TYPE,
            EGL_WINDOW_BIT,
            EGL_NONE
    };

    if (EGL_TRUE != eglChooseConfig(display, configSpec, &config, 1, &configNum)) {
        LOGE("%s", "eglChooseConfig failed!");
        return;
    }
    //创建surface
    winSurface = eglCreateWindowSurface(display, config, nativeWindow, 0);

    if (winSurface == EGL_NO_SURFACE) {
        LOGE("%s", "eglCreateWindowSurface failed!");
        return;
    }
    //创建context
    const EGLint ctxAttr[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
    };
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxAttr);
    if (context == EGL_NO_CONTEXT) {
        LOGE("%s", "eglCreateContext failed!");
        return;
    }
    //egl 关联 openl
    if (EGL_TRUE != eglMakeCurrent(display, winSurface, winSurface, context)) {
        LOGE("%s", "eglMakeCurrent failed!");
        return;
    }
    LOGI("%s", "egl init success!");

    //2.初始化GPUImageRender
    ben::ngp::GPUImageRender *render = getNativeClassPtr<ben::ngp::GPUImageRender>(
            GPU_IMAGE_RENDER_CLASS);
    if (!render) {
        LOGE("%s", "render is null");
        return;
    }

    //gl background
    glClearColor(render->getBackgroundRed(), render->getBackgroundGreen(),
                 render->getBackgroundBlue(), 1);
    glDisable(GL_DEPTH_TEST);

    //构造默认filter
    render->setIsPreparGLEnvironment(JNI_TRUE);

    ben::ngp::GPUImageFilter *filter = new ben::ngp::GPUImageFilter();
    filter->setNativeWindow(nativeWindow);
    filter->setEglDisplay(&display);
    filter->setEglSurface(&winSurface);
    render->setFilter(filter);

    //filter init
    render->getFilter()->ifNeedInit();
}

void ben::ngp::GPUImageRender::nativeSurfaceChanged(JNIEnv *env, jclass javaThis, jint width,
                                                    jint height) {
    ben::ngp::GPUImageRender *render = getNativeClassPtr<ben::ngp::GPUImageRender>(
            GPU_IMAGE_RENDER_CLASS);
    if (!render->isIsPreparGLEnvironment()) {
        LOGE("%s", "opengl environment is not ready!");
        return;
    }
    render->surfaceChange(width, height);
}

void ben::ngp::GPUImageRender::nativeDestroyed(JNIEnv *env, jclass javaThis) {
    LOGI("%s", "GPUImageRender nativeDestroyed");

    this->getFilter()->destory();

    eglMakeCurrent(eglDisp, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(eglDisp, eglCtx);
    eglDestroySurface(eglDisp, eglSurface);
    eglTerminate(eglDisp);

    eglDisp = EGL_NO_DISPLAY;
    eglSurface = EGL_NO_SURFACE;
    eglCtx = EGL_NO_CONTEXT;
}

void ben::ngp::GPUImageRender::nativeDestorySurfaceGL(JNIEnv *env, jclass javaThis) {
    this->getFilter()->destory();

    eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(display, context);
    eglDestroySurface(display, winSurface);
    eglTerminate(display);

    display = EGL_NO_DISPLAY;
    winSurface = EGL_NO_SURFACE;
    context = EGL_NO_CONTEXT;

}

void ben::ngp::GPUImageRender::nativeCreateGL(JNIEnv *env, jclass javaThis) {
    const EGLint confAttr[] =
            {
                    EGL_RED_SIZE, 8,
                    EGL_GREEN_SIZE, 8,
                    EGL_BLUE_SIZE, 8,
                    EGL_ALPHA_SIZE, 8,
                    EGL_DEPTH_SIZE, 16,
                    EGL_STENCIL_SIZE, 0,
                    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                    EGL_SURFACE_TYPE,
                    EGL_PBUFFER_BIT,
                    EGL_NONE
            };
    const EGLint ctxAttr[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
    };
    // surface attributes
    const EGLint surfaceAttr[] = {
            EGL_WIDTH, MAX_FBO_SURFACE_WIDTH,
            EGL_HEIGHT, MAX_FBO_SURFACE_HEIGHT,
            EGL_NONE
    };
    EGLint numConfigs;

    eglDisp = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (eglDisp == EGL_NO_DISPLAY) {
        //Unable to open connection to local windowing system
        LOGI("%s", "Unable to open connection to local windowing system");
    }
    if (!eglInitialize(eglDisp, NULL, NULL)) {
        // Unable to initialize EGL. Handle and recover
        LOGI("%s", "Unable to initialize EGL");
    }
    // choose the first config, i.e. best config
    if (!eglChooseConfig(eglDisp, confAttr, &eglConf, 1, &numConfigs)) {
        LOGI("%s", "some config is wrong");
    } else {
        LOGI("%s", "all configs is OK");
    }
    // create a pixelbuffer surface
    eglSurface = eglCreatePbufferSurface(eglDisp, eglConf, surfaceAttr);
    if (eglSurface == EGL_NO_SURFACE) {
        switch (eglGetError()) {
            case EGL_BAD_ALLOC:
                // Not enough resources available. Handle and recover
                LOGI("%s", "Not enough resources available");
                break;
            case EGL_BAD_CONFIG:
                // Verify that provided EGLConfig is valid
                LOGI("%s", "provided EGLConfig is invalid");
                break;
            case EGL_BAD_PARAMETER:
                // Verify that the EGL_WIDTH and EGL_HEIGHT are
                // non-negative values
                LOGI("%s", "provided EGL_WIDTH and EGL_HEIGHT is invalid");
                break;
            case EGL_BAD_MATCH:
                // Check window and EGLConfig attributes to determine
                // compatibility and pbuffer-texture parameters
                LOGI("%s", "Check window and EGLConfig attributes");
                break;
        }
    }
    eglCtx = eglCreateContext(eglDisp, eglConf, EGL_NO_CONTEXT, ctxAttr);
    if (eglCtx == EGL_NO_CONTEXT) {
        EGLint error = eglGetError();
        if (error == EGL_BAD_CONFIG) {
            // Handle error and recover
            LOGI("%s", "EGL_BAD_CONFIG");
        }
    }
    if (!eglMakeCurrent(eglDisp, eglSurface, eglSurface, eglCtx)) {
        LOGI("%s", "MakeCurrent failed");
    }
    LOGI("%s", "initialize success!");

    //2.初始化GPUImageRender
    ben::ngp::GPUImageRender *render = getNativeClassPtr<ben::ngp::GPUImageRender>(
            GPU_IMAGE_RENDER_CLASS);
    if (!render) {
        LOGE("%s", "render is null");
        return;
    }

    //gl background
    glClearColor(render->getBackgroundRed(), render->getBackgroundGreen(),
                 render->getBackgroundBlue(), 1);
    glDisable(GL_DEPTH_TEST);

    //构造默认filter
    render->setIsPreparGLEnvironment(JNI_TRUE);

    ben::ngp::GPUImageFilter *filter = new ben::ngp::GPUImageFilter();
    filter->setIsFBO(true);
    filter->setEglDisplay(&eglDisp);
    filter->setEglSurface(&eglSurface);
    render->setFilter(filter);
    //filter init
    render->getFilter()->ifNeedInit();

}


ben::ngp::GPUImageRender::GPUImageRender() : JavaClass() {

}

ben::ngp::GPUImageRender::GPUImageRender(ben::ngp::GPUImageFilter *filter) {
    this->filter = filter;
}

ben::ngp::GPUImageRender::GPUImageRender(JNIEnv *env) : JavaClass(env) {
    initialize(env);
}

ben::ngp::GPUImageRender::~GPUImageRender() {

}

void ben::ngp::GPUImageRender::initialize(JNIEnv *env) {
    setClass(env);
    glCubeBuffer = CUBE;
    glTextureBuffer = TEXTURE_NO_ROTATION;
    setRotation(Rotation::NORMAL, false, false);
}


void ben::ngp::GPUImageRender::mapFields() {

}

const char *ben::ngp::GPUImageRender::getCanonicalName() const {
    return GPU_IMAGE_RENDER_CLASS;
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


int *ben::ngp::GPUImageRender::getGlRgbBuffer() const {
    return glRgbBuffer;
}

void ben::ngp::GPUImageRender::setGlRgbBuffer(int *glRgbBuffer) {
    GPUImageRender::glRgbBuffer = glRgbBuffer;
}

float ben::ngp::GPUImageRender::getBackgroundRed() const {
    return backgroundRed;
}

void ben::ngp::GPUImageRender::setBackgroundRed(float backgroundRed) {
    GPUImageRender::backgroundRed = backgroundRed;
}

float ben::ngp::GPUImageRender::getBackgroundGreen() const {
    return backgroundGreen;
}

void ben::ngp::GPUImageRender::setBackgroundGreen(float backgroundGreen) {
    GPUImageRender::backgroundGreen = backgroundGreen;
}

float ben::ngp::GPUImageRender::getBackgroundBlue() const {
    return backgroundBlue;
}

void ben::ngp::GPUImageRender::setBackgroundBlue(float backgroundBlue) {
    GPUImageRender::backgroundBlue = backgroundBlue;
}

bool ben::ngp::GPUImageRender::isFlipHorizontal() const {
    return flipHorizontal;
}

void ben::ngp::GPUImageRender::setFlipHorizontal(bool flipHorizontal) {
    GPUImageRender::flipHorizontal = flipHorizontal;
}

bool ben::ngp::GPUImageRender::isFlipVertical() const {
    return flipVertical;
}

void ben::ngp::GPUImageRender::setFlipVertical(bool flipVertical) {
    GPUImageRender::flipVertical = flipVertical;
}

ScaleType ben::ngp::GPUImageRender::getScaleType() const {
    return scaleType;
}

void ben::ngp::GPUImageRender::setScaleType(ScaleType scaleType) {
    if (this->scaleType == scaleType)
        return;
    GPUImageRender::scaleType = scaleType;
}

void ben::ngp::GPUImageRender::adjustImageScaling() {
    float outputWidth = this->getOutputWidth();
    float outputHeight = this->getOutputHeight();
    if (rotation == Rotation::ROTATION_270 || rotation == Rotation::ROTATION_90) {
        outputWidth = this->getOutputHeight();
        outputHeight = this->getOutputWidth();
    }

    float ratio1 = outputWidth / imageWidth;
    float ratio2 = outputHeight / imageHeight;

    float ratioMax = max(ratio1, ratio2);
    int imageWidthNew = round(imageWidth * ratioMax);
    int imageHeightNew = round(imageHeight * ratioMax);

    float ratioWidth = imageWidthNew / outputWidth;
    float ratioHeight = imageHeightNew / outputHeight;

    float *cube = CUBE;
    float *textureCords = ben::util::getRotation(rotation, flipHorizontal, flipVertical);
    if (scaleType == ScaleType::CENTER_CROP) {
        float distHorizontal = (1 - 1 / ratioWidth) / 2;
        float distVertical = (1 - 1 / ratioHeight) / 2;
        textureCords = new float[8]{
                addDistance(textureCords[0], distHorizontal),
                addDistance(textureCords[1], distVertical),
                addDistance(textureCords[2], distHorizontal),
                addDistance(textureCords[3], distVertical),
                addDistance(textureCords[4], distHorizontal),
                addDistance(textureCords[5], distVertical),
                addDistance(textureCords[6], distHorizontal),
                addDistance(textureCords[7], distVertical),
        };
    } else {
        cube = new float[8]{
                CUBE[0] / ratioHeight, CUBE[1] / ratioWidth,
                CUBE[2] / ratioHeight, CUBE[3] / ratioWidth,
                CUBE[4] / ratioHeight, CUBE[5] / ratioWidth,
                CUBE[6] / ratioHeight, CUBE[7] / ratioWidth,
        };
    }

    this->glCubeBuffer = cube;
    this->glTextureBuffer = textureCords;
}

float ben::ngp::GPUImageRender::addDistance(float coordinate, float distance) {
    return coordinate == 0.0f ? distance : 1 - distance;

}

ben::ngp::GPUImageFilter *ben::ngp::GPUImageRender::getFilter() const {
    return filter;
}

void ben::ngp::GPUImageRender::setFilter(ben::ngp::GPUImageFilter *filter) {
    GPUImageRender::filter = filter;
}

float *ben::ngp::GPUImageRender::getGlCubeBuffer() const {
    return glCubeBuffer;
}

float *ben::ngp::GPUImageRender::getGlTextureBuffer() const {
    return glTextureBuffer;
}

Rotation ben::ngp::GPUImageRender::getRotation() const {
    return rotation;
}

void ben::ngp::GPUImageRender::setRotation(Rotation rotation) {
    GPUImageRender::rotation = rotation;
}

void
ben::ngp::GPUImageRender::setRotation(Rotation rotation, bool flipHorizontal, bool flipVertical) {
    if (rotation == this->rotation)
        return;

    this->flipHorizontal = flipHorizontal;
    this->flipVertical = flipVertical;
    setRotation(rotation);

}

void ben::ngp::GPUImageRender::resetFilter(ben::ngp::GPUImageFilter *filter) {
    filter->setNativeWindow(nativeWindow);
    filter->setEglDisplay(&display);
    filter->setEglSurface(&winSurface);
    if (dynamic_cast<GPUImageFilterGroup *>(filter) != NULL) {
        GPUImageFilterGroup *filterGroup = dynamic_cast<GPUImageFilterGroup *>(filter);
        for (ben::ngp::GPUImageFilter *filter : filterGroup->getFilters()) {
            filter->setNativeWindow(nativeWindow);
            filter->setEglDisplay(&display);
            filter->setEglSurface(&winSurface);
        }
        for (ben::ngp::GPUImageFilter *filter : filterGroup->getMergedFilters()) {
            filter->setNativeWindow(nativeWindow);
            filter->setEglDisplay(&display);
            filter->setEglSurface(&winSurface);
        }
    }
    this->setFilter(filter);
    this->getFilter()->ifNeedInit();

    glUseProgram(this->getFilter()->getGlProgId());
    this->surfaceChange(this->getOutputWidth(), this->getOutputHeight());

}


void ben::ngp::GPUImageRender::renderBitmap(JNIEnv *env, jobject jbitmap) {
    AndroidBitmapInfo bitmapInfo;
    if (AndroidBitmap_getInfo(env, jbitmap, &bitmapInfo) < 0) {
        return;
    }
    int bitmapWidth = bitmapInfo.width;
    int bitmapHeight = bitmapInfo.height;
    LOGI("showBitmap width %d, height %d, format %d", bitmapWidth, bitmapHeight,
         bitmapInfo.format);
    if (bitmapInfo.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGE("%s", "invalid rgb format error!");
        return;
    }
    this->setGlTextureId(
            loadTextureByBitmap(env, jbitmap, bitmapWidth, bitmapHeight, this->getGlTextureId()));
    LOGI("gl textureid %d", this->getGlTextureId());
    this->setImageWidth(bitmapWidth);
    this->setImageHeight(bitmapHeight);

    adjustImageScaling();

}

void ben::ngp::GPUImageRender::renderYUV420(JNIEnv *env, void* rgb, jint width, jint height) {
    this->setGlTextureId(
            loadTextureByPixel(rgb, width, height, this->getGlTextureId()));
    this->setImageWidth(width);
    this->setImageHeight(height);
    adjustImageScaling();
    reqeustRender();
}

void ben::ngp::GPUImageRender::surfaceChange(int width, int height) {
    //reset width height。
    int windowWidth = width;
    int windowHeight = height;
    /* if (windowWidth > windowHeight) {
         windowHeight = width;
         windowWidth = height;
     }*/
    this->setOutputWidth(windowWidth);
    this->setOutputHeight(windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);
    glUseProgram(this->getFilter()->getGlProgId());
    this->getFilter()->onOutputSizeChanged(windowWidth, windowHeight);
    this->adjustImageScaling();
}

void ben::ngp::GPUImageRender::reqeustRender() {
    //draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->getFilter()->onDraw(this->getGlTextureId(), this->getGlCubeBuffer(),
                              this->getGlTextureBuffer());

}

