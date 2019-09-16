//
// Created by ben622 on 2019/9/16.
//
#ifndef NATIVEGPUIMAGE_OPEN_GL_UTIL_HPP
#define NATIVEGPUIMAGE_OPEN_GL_UTIL_HPP

#include "../include/jni/JniHelpers.h"

namespace ben {
    namespace util {
        static int NO_TEXTURE = -1;

        static int loadShader(const char *strSource, int iType) {
            GLint sh = glCreateShader(iType);
            if (sh == 0) {
                LOGE(" glCreateShader  %d failed ! ", iType);
                return 0;
            }
            glShaderSource(sh, 1, &strSource, 0);
            glCompileShader(sh);
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

    }
}

#endif //NATIVEGPUIMAGE_OPEN_GL_UTIL_HPP
