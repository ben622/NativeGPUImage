//
// Created by ben622 on 2019/9/28.
//

#include "gpu_image_two_input_filter.hpp"

ben::ngp::GPUImageTwoInputFilter::GPUImageTwoInputFilter(char *fragmentShader)
        : GPUImageFilter(TWO_INPUT_VERTEX_SHADER, fragmentShader) {
    setRotation(ben::util::Rotation::NORMAL, false, false);
}

ben::ngp::GPUImageTwoInputFilter::GPUImageTwoInputFilter(char *fragmentShader, JNIEnv *env)
        : GPUImageFilter(TWO_INPUT_VERTEX_SHADER,
                         fragmentShader,
                         env) {
    setRotation(ben::util::Rotation::NORMAL, false, false);
}

ben::ngp::GPUImageTwoInputFilter::GPUImageTwoInputFilter(char *vertexShader, char *fragmentShader,
                                                         JNIEnv *env) : GPUImageFilter(vertexShader,
                                                                                       fragmentShader,
                                                                                       env) {
    setRotation(ben::util::Rotation::NORMAL, false, false);

}

void ben::ngp::GPUImageTwoInputFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "bitmap", kTypeBitmap);
    cacheConstructor(env);
    cacheMethod(env, "getBitmap", kTypeBitmap, NULL);
    cacheMethod(env, "setBitmap", kTypeVoid, kTypeBitmap, NULL);
    merge(this);
}

void ben::ngp::GPUImageTwoInputFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("bitmap", kTypeBitmap, &bitmap);
}

const char *ben::ngp::GPUImageTwoInputFilter::getCanonicalName() const {
    return JAVA_TWO_INPUT_FILTER;
}

void ben::ngp::GPUImageTwoInputFilter::onInit() {
    GPUImageFilter::onInit();
    filterSecondTextureCoordinateAttribute = glGetAttribLocation(getGlProgId(),
                                                                 "inputTextureCoordinate2");
    filterInputTextureUniform2 = glGetUniformLocation(getGlProgId(),
                                                      "inputImageTexture2"); // This does assume a name of "inputImageTexture2" for second input texture in the fragment shader
    glEnableVertexAttribArray(filterSecondTextureCoordinateAttribute);
}

void ben::ngp::GPUImageTwoInputFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    if (bitmap != NULL) {
        setBitmap(bitmap);
    }
}

void ben::ngp::GPUImageTwoInputFilter::onDrawArraysPre() {
    GPUImageFilter::onDrawArraysPre();
    glEnableVertexAttribArray(filterSecondTextureCoordinateAttribute);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, filterSourceTexture2);
    glUniform1i(filterInputTextureUniform2, 3);

    glVertexAttribPointer(filterSecondTextureCoordinateAttribute, 2, GL_FLOAT, false, 0,
                          texture2CoordinatesBuffer);
}

void ben::ngp::GPUImageTwoInputFilter::setBitmap(jobject jbitmap) {
    GPUImageTwoInputFilter::bitmap = jbitmap;
    addDrawThread(GPUImageTwoInputFilter::setBitmapCallback, this);
}

void ben::ngp::GPUImageTwoInputFilter::setBitmapCallback(void *arg) {
    GPUImageTwoInputFilter *filter = static_cast<GPUImageTwoInputFilter *>(arg);
    if (filter->filterSourceTexture2 == NO_TEXTURE) {
        if (filter->pxiel == NULL||filter->getBitmapWidth()==0||filter->getBitmapHeight()==0) {
            return;
        }
        glActiveTexture(GL_TEXTURE3);
        filter->filterSourceTexture2 = loadTextureByPixel(filter->getPxiel(), filter->getBitmapWidth(),
                filter->getBitmapHeight(), NO_TEXTURE);

    }

}

void
ben::ngp::GPUImageTwoInputFilter::setRotation(ben::util::Rotation rotation, bool flipHorizontal,
                                              bool flipVertical) {
    texture2CoordinatesBuffer = getRotation(rotation, flipHorizontal, flipVertical);
}

void ben::ngp::GPUImageTwoInputFilter::onDestory() {
    GPUImageFilter::onDestory();
    glDeleteTextures(1, (const GLuint *) new int[1]{
            filterSourceTexture2
    });
    filterSourceTexture2 = NO_TEXTURE;
}

void *ben::ngp::GPUImageTwoInputFilter::getPxiel() const {
    return pxiel;
}

void ben::ngp::GPUImageTwoInputFilter::setPxiel(void *pxiel) {
    GPUImageTwoInputFilter::pxiel = pxiel;
}

int ben::ngp::GPUImageTwoInputFilter::getBitmapWidth() const {
    return bitmapWidth;
}

void ben::ngp::GPUImageTwoInputFilter::setBitmapWidth(int bitmapWidth) {
    GPUImageTwoInputFilter::bitmapWidth = bitmapWidth;
}

int ben::ngp::GPUImageTwoInputFilter::getBitmapHeight() const {
    return bitmapHeight;
}

void ben::ngp::GPUImageTwoInputFilter::setBitmapHeight(int bitmapHeight) {
    GPUImageTwoInputFilter::bitmapHeight = bitmapHeight;
}

const _jobject *ben::ngp::GPUImageTwoInputFilter::getBitmap() const {
    return bitmap;
}

