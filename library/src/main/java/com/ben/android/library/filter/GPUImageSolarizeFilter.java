package com.ben.android.library.filter;

import android.support.annotation.FloatRange;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/8
 */
public class GPUImageSolarizeFilter extends NativeFilter {
    private float threshold;

    public GPUImageSolarizeFilter() {
        this(0.5f);
    }

    public GPUImageSolarizeFilter(@FloatRange(from = 0.0f,to = 1.0f) float threshold) {
        super(FilterType.SOLARIZE.ordinal());
        this.threshold = threshold;
    }

    public float getThreshold() {
        return threshold;
    }

    public void setThreshold(float threshold) {
        this.threshold = threshold;
    }
}
