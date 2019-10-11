//
// Created by ben622 on 2019/9/18.
//

#ifndef NATIVEGPUIMAGE_SCALE_TYPE_HPP
#define NATIVEGPUIMAGE_SCALE_TYPE_HPP
namespace ben{
    namespace util{
        enum ScaleType{
            CENTER_INSIDE, CENTER_CROP
        };
        static ScaleType fromScaleValue(int scale) {
            switch (scale) {
                case 0:
                    return CENTER_INSIDE;
                case 1:
                    return CENTER_CROP;
                default:
                    throw ben::common::NException(" is an unknown rotation. Needs to be either 0, 90, 180 or 270!");
            }
        }
    }
}
#endif //NATIVEGPUIMAGE_SCALE_TYPE_HPP
