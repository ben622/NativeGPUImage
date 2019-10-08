package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/8
 */
public class GPUImageHalftoneFilter extends NativeFilter {
    private float fractionalWidthOfAPixel;

    public GPUImageHalftoneFilter() {
        this(0.01f);
    }

    public GPUImageHalftoneFilter(float fractionalWidthOfAPixel) {
        super(FilterType.HALFTONE.ordinal());
        this.fractionalWidthOfAPixel = fractionalWidthOfAPixel;
    }

    public float getFractionalWidthOfAPixel() {
        return fractionalWidthOfAPixel;
    }

    public void setFractionalWidthOfAPixel(float fractionalWidthOfAPixel) {
        this.fractionalWidthOfAPixel = fractionalWidthOfAPixel;
    }


}
