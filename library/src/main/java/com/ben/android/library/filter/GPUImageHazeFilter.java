package com.ben.android.library.filter;

import android.support.annotation.FloatRange;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/8
 */
public class GPUImageHazeFilter extends NativeFilter {
    private float distance;
    private float slope;

    public GPUImageHazeFilter() {
        this(0.2f, 0.0f);
    }

    public GPUImageHazeFilter(@FloatRange(from = -0.3f, to = 0.3f) float distance, @FloatRange(from = -0.3f, to = 0.3f) float slope) {
        super(FilterType.HAZE.ordinal());
        this.distance = distance;
        this.slope = slope;
    }

    public float getDistance() {
        return distance;
    }

    public void setDistance(float distance) {
        this.distance = distance;
    }

    public float getSlope() {
        return slope;
    }

    public void setSlope(float slope) {
        this.slope = slope;
    }
}
