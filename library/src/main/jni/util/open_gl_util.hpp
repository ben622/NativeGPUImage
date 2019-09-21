//
// Created by ben622 on 2019/9/16.
//
#ifndef NATIVEGPUIMAGE_OPEN_GL_UTIL_HPP
#define NATIVEGPUIMAGE_OPEN_GL_UTIL_HPP

#include "../include/jni/JniHelpers.h"
#include <android/bitmap.h>

namespace ben {
    namespace util {
        static int NO_TEXTURE = -1;

        static int loadShader(const char *strSource, int iType) {
            GLint sh = glCreateShader(iType);
            if (sh == 0) {
                LOGE(" glCreateShader  %d failed ! ", iType);
                return 0;
            }
            glShaderSource(sh, 1, &strSource, NULL);
            glCompileShader(sh);
            GLint compiled = 0;
            glGetShaderiv(sh, GL_COMPILE_STATUS, &compiled);
            if (!compiled) {
                GLint infoLen = 0;
                glGetShaderiv(sh, GL_INFO_LOG_LENGTH, &infoLen);
                if (infoLen) {
                    char* buf = (char*) malloc(infoLen);
                    if (buf) {
                        glGetShaderInfoLog(sh, infoLen, NULL, buf);
                        LOGE("Could not compile shader %d:\n%s\n",
                             iType, buf);
                        free(buf);
                    }
                    glDeleteShader(sh);
                    sh = 0;
                }
            }
            return sh;
        }

        static int loadProgram(const char *strVSource, const char *strFSource) {
            int iVShader;
            int iFShader;
            int iProgId;
            iVShader = loadShader(strVSource, GL_VERTEX_SHADER);
            if (iVShader == 0) {
                LOGE("Load Program %s", "Vertex Shader Failed");
                return 0;
            }
            iFShader = loadShader(strFSource, GL_FRAGMENT_SHADER);
            if (iFShader == 0) {
                LOGE("Load Program %s", "Fragment Shader Failed");
                return 0;
            }
            iProgId = glCreateProgram();
            glAttachShader(iProgId, iVShader);
            glAttachShader(iProgId, iFShader);
            glLinkProgram(iProgId);
            glDeleteShader(iVShader);
            glDeleteShader(iFShader);
            return iProgId;
        }

        /**
         * 根据Bitmap对象生成纹理
         * @param env
         * @param jbitmap
         * @param width
         * @param height
         * @param usedTexId
         * @return
         */
        static GLuint loadTextureByBitmap(JNIEnv *env,jobject jbitmap,int width,int height,int usedTexId) {
            void* pixel_source = NULL;
            AndroidBitmap_lockPixels(env, jbitmap, &pixel_source);
            GLuint renderbuffers;
            if (usedTexId == NO_TEXTURE) {
                glGenTextures(1, &renderbuffers);
                glBindTexture(GL_TEXTURE_2D, renderbuffers);
                glTexParameterf(GL_TEXTURE_2D,
                                GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D,
                                GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D,
                                GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameterf(GL_TEXTURE_2D,
                                GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                             pixel_source);
            } else {
                glBindTexture(GL_TEXTURE_2D, renderbuffers);
                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE,
                                pixel_source);
            }
            AndroidBitmap_unlockPixels(env, jbitmap);
            return renderbuffers;
        }


    }
}

#endif //NATIVEGPUIMAGE_OPEN_GL_UTIL_HPP
