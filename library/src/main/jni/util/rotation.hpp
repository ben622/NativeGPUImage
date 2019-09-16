//
// Created by ben622 on 2019/9/16.
//

#ifndef NATIVEGPUIMAGE_ROTATION_HPP
#define NATIVEGPUIMAGE_ROTATION_HPP

#include "../libcommon/native_exception.hpp"
namespace ben {
    namespace util {
        static enum Rotation {
            NORMAL, ROTATION_90, ROTATION_180, ROTATION_270
        };

        static int asInt(Rotation rotation) {
            switch (rotation) {
                case NORMAL:
                    return 0;
                case ROTATION_90:
                    return 90;
                case ROTATION_180:
                    return 180;
                case ROTATION_270:
                    return 270;
                default:
                    throw ben::common::NException("Unknown Rotation!");
            }
        }

         static Rotation fromInt(int rotation) {
            switch (rotation) {
                case 0:
                    return NORMAL;
                case 90:
                    return ROTATION_90;
                case 180:
                    return ROTATION_180;
                case 270:
                    return ROTATION_270;
                case 360:
                    return NORMAL;
                default:
                    throw ben::common::NException(" is an unknown rotation. Needs to be either 0, 90, 180 or 270!");
            }
        }
    }
}

#endif //NATIVEGPUIMAGE_ROTATION_HPP
