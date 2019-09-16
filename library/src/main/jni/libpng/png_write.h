//
// Created by 唐宇 on 2018/5/22.
//

#ifndef OPENGLTEXTURE_PNG_WRITE_H
#define OPENGLTEXTURE_PNG_WRITE_H
extern "C" {
#include "./image.h"
}


class PngWrite {
public:
    PngWrite();
    bool writePngFile(const char *pngPaht, png_uint_32 width, png_uint_32 height,png_byte* pixel);

};


#endif //OPENGLTEXTURE_PNG_WRITE_H
