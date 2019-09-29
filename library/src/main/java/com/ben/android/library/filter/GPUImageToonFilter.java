package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/29
 */
public class GPUImageToonFilter extends GPUImage3x3TextureSamplingFilter {
    private float threshold;
    private float quantizationLevels;

    public GPUImageToonFilter() {
        this(0.2f, 10.0f);
    }

    public GPUImageToonFilter(float threshold, float quantizationLevels) {
        super(FilterType.TOON.ordinal());
        this.threshold = threshold;
        this.quantizationLevels = quantizationLevels;
    }

    public float getThreshold() {
        return threshold;
    }

    public void setThreshold(float threshold) {
        this.threshold = threshold;
    }

    public float getQuantizationLevels() {
        return quantizationLevels;
    }

    public void setQuantizationLevels(float quantizationLevels) {
        this.quantizationLevels = quantizationLevels;
    }
}
