package com.ben.android.library.filter;

import android.support.annotation.FloatRange;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/8
 */
public class GPUImageSharpenFilter extends NativeFilter {
    private float sharpness;

    public GPUImageSharpenFilter() {
        this(0.0f);
    }

    public GPUImageSharpenFilter(@FloatRange(from = -4.0f, to = 4.0f) float sharpness) {
        super(FilterType.SHARPEN.ordinal());
        this.sharpness = sharpness;
    }

    public float getSharpness() {
        return sharpness;
    }

    public void setSharpness(float sharpness) {
        this.sharpness = sharpness;
    }
}

