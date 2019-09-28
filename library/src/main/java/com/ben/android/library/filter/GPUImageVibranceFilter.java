package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/28
 */
public class GPUImageVibranceFilter extends NativeFilter {
    private float vibrance;

    public GPUImageVibranceFilter() {
        this(0f);
    }

    public GPUImageVibranceFilter(float vibrance) {
        super(FilterType.VIBRANCE.ordinal());
        this.vibrance = vibrance;
    }

    public float getVibrance() {
        return vibrance;
    }

    public void setVibrance(float vibrance) {
        this.vibrance = vibrance;
    }
}

