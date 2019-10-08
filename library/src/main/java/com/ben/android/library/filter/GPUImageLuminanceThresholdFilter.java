package com.ben.android.library.filter;

import android.support.annotation.FloatRange;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/8
 */
public class GPUImageLuminanceThresholdFilter extends NativeFilter {
    private float threshold;

    public GPUImageLuminanceThresholdFilter() {
        this(0.5f);
    }

    public GPUImageLuminanceThresholdFilter(@FloatRange(from = 0.0f,to = 1.0f) float threshold) {
        super(FilterType.LUMINANCE_THRESHSOLD.ordinal());
        this.threshold = threshold;
    }

    public float getThreshold() {
        return threshold;
    }

    public void setThreshold(float threshold) {
        this.threshold = threshold;
    }
}
