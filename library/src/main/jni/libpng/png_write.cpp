//
// Created by 唐宇 on 2018/5/22.
//

#include <stdio.h>
#include "png_write.h"



PngWrite::PngWrite() {

}

bool PngWrite::writePngFile(const char *pngPaht, png_uint_32 width, png_uint_32 height,png_byte* pixel) {
    FILE* fp;

    png_structp png_ptr;
    png_infop info_ptr;
    png_colorp palette;

    fp=fopen(pngPaht,"wb");
    if (fp == NULL)
        return false;
    png_ptr=png_create_write_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
    if (png_ptr == NULL)
    {
        fclose(fp);
        return false;
    }
    /* 分配内存并初始化图像信息数据。（必要）*/
    info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr){
        fclose(fp);
        png_destroy_write_struct(&png_ptr,NULL);
        return false;
    }

    if(setjmp(png_jmpbuf(png_ptr))){
        /* 如果程序跑到这里了，那么写入文件时出现了问题 */
        fclose(fp);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return false;
    }
    /* 设置输出控制，如果你使用的是 C 的标准 I/O 流 */
    png_init_io(png_ptr, fp);

    /* 这是一种复杂的做法 */

    /* （必需）在这里设置图像的信息，宽度、高度的上限是 2^31。
     * bit_depth 每个颜色的位深，取值必需是 1、2、4、8 或者 16, 但是可用的值也依赖于 color_type。
     * color_type 可选值有： PNG_COLOR_TYPE_GRAY、PNG_COLOR_TYPE_GRAY_ALPHA、
     * PNG_COLOR_TYPE_PALETTE、PNG_COLOR_TYPE_RGB、PNG_COLOR_TYPE_RGB_ALPHA。
     * interlace 可以是 PNG_INTERLACE_NONE 或 PNG_INTERLACE_ADAM7,
     * 而 compression_type 和 filter_type 目前必需是 PNG_COMPRESSION_TYPE_BASE
     * 和 and PNG_FILTER_TYPE_BASE。
     */
    png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB_ALPHA,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    /* 写入文件头部信息（必需） */
    png_write_info(png_ptr, info_ptr);

    png_bytep row_pointers[height];
    png_uint_32 k;
    /* 将这些像素行指针指向你的 "image" 字节数组中对应的位置，即：指向每行像素的起始处 */
    for (k = 0; k < height; k++)
        row_pointers[k] = pixel + k*width*4;

    /* 一次调用就将整个图像写进文件 */
    png_write_image(png_ptr, row_pointers);
    /* 必需调用这个函数完成写入文件其余部分 */
    png_write_end(png_ptr, info_ptr);
    /* 写完后清理并释放已分配的内存 */
    png_destroy_write_struct(&png_ptr, &info_ptr);
    /* 关闭文件 */
    fclose(fp);

    return false;
}

