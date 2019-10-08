package com.ben.android.library.filter;

import android.support.annotation.IntRange;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/8
 */
public class GPUImageRGBDilationFilter extends NativeFilter {
    private int radius;

    public GPUImageRGBDilationFilter() {
        this(1);
    }

    public GPUImageRGBDilationFilter(@IntRange(from = 0,to = 4) int radius) {
        super(FilterType.RGB_DILATION.ordinal());
        this.radius = radius;
    }

    public int getRadius() {
        return radius;
    }

    public void setRadius(int radius) {
        this.radius = radius;
    }
}
