package com.ben.android.library.filter;

import android.support.annotation.FloatRange;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/8
 */
public class GPUImageThresholdEdgeDetectionFilter extends NativeFilter {
    private float size;
    private float threshold;

    public GPUImageThresholdEdgeDetectionFilter() {
        this(0.9f, 0.9f);
    }

    public GPUImageThresholdEdgeDetectionFilter(@FloatRange(from = 0.0f,to = 5.0f) float size, float threshold) {
        super(FilterType.THRESHOLD_EDGE_DETECTION.ordinal());
        this.size = size;
        this.threshold = threshold;
    }

    public float getSize() {
        return size;
    }

    public void setSize(float size) {
        this.size = size;
    }

    public float getThreshold() {
        return threshold;
    }

    public void setThreshold(float threshold) {
        this.threshold = threshold;
    }
}
