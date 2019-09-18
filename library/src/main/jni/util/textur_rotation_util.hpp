//
// Created by ben622 on 2019/9/16.
//

#ifndef NATIVEGPUIMAGE_TEXTUR_ROTATION_UTIL_HPP
#define NATIVEGPUIMAGE_TEXTUR_ROTATION_UTIL_HPP

#include "../include/jni/JniHelpers.h"
#include "rotation.hpp"

namespace ben {
    namespace util {
        static float CUBE[8] = {
                -1.0f, -1.0f,
                1.0f, -1.0f,
                -1.0f, 1.0f,
                1.0f, 1.0f,
        };
        static float TEXTURE_NO_ROTATION[8] = {
                0.0f, 1.0f,
                1.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 0.0f,
        };

        static float TEXTURE_ROTATED_90[8] = {
                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 1.0f,
                0.0f, 0.0f,
        };
        static float TEXTURE_ROTATED_180[8] = {
                1.0f, 0.0f,
                0.0f, 0.0f,
                1.0f, 1.0f,
                0.0f, 1.0f,
        };
        static float TEXTURE_ROTATED_270[8] = {
                0.0f, 0.0f,
                0.0f, 1.0f,
                1.0f, 0.0f,
                1.0f, 1.0f,
        };

        static float flip(float i) {
            if (i == 0.0f) {
                return 1.0f;
            }
            return 0.0f;
        }

        static float *getRotation(Rotation rotation, bool flipHorizontal,
                           bool flipVertical) {
            float *rotatedTex = TEXTURE_NO_ROTATION;
            switch (rotation) {
                case ROTATION_90:
                    rotatedTex = TEXTURE_ROTATED_90;
                    break;
                case ROTATION_180:
                    rotatedTex = TEXTURE_ROTATED_180;
                    break;
                case ROTATION_270:
                    rotatedTex = TEXTURE_ROTATED_270;
                    break;
                case NORMAL:
                default:
                    rotatedTex = TEXTURE_NO_ROTATION;
                    break;
            }
            if (flipHorizontal) {
                rotatedTex = new float[8]{
                        flip(rotatedTex[0]), rotatedTex[1],
                        flip(rotatedTex[2]), rotatedTex[3],
                        flip(rotatedTex[4]), rotatedTex[5],
                        flip(rotatedTex[6]), rotatedTex[7],
                };
            }
            if (flipVertical) {
                rotatedTex = new float[8]{
                        rotatedTex[0], flip(rotatedTex[1]),
                        rotatedTex[2], flip(rotatedTex[3]),
                        rotatedTex[4], flip(rotatedTex[5]),
                        rotatedTex[6], flip(rotatedTex[7]),
                };
            }
            return rotatedTex;
        }

    }
}
#endif //NATIVEGPUIMAGE_TEXTUR_ROTATION_UTIL_HPP
