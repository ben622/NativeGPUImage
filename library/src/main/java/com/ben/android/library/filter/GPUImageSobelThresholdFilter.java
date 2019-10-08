package com.ben.android.library.filter;

import android.support.annotation.FloatRange;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/8
 */
public class GPUImageSobelThresholdFilter extends GPUImage3x3TextureSamplingFilter {
    private float threshold;

    public GPUImageSobelThresholdFilter() {
        this(0.9f);
    }

    public GPUImageSobelThresholdFilter(float threshold) {
        super(FilterType.SOBEL_THRESHOLD.ordinal());
        this.threshold = threshold;
    }

    public float getThreshold() {
        return threshold;
    }

    public void setThreshold(float threshold) {
        this.threshold = threshold;
    }
}
