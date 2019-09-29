package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/29
 */
public class GPUImageExposureFilter extends NativeFilter{
    private float exposure;

    public GPUImageExposureFilter() {
        this(1.0f);
    }

    public GPUImageExposureFilter(float exposure) {
        super(FilterType.EXPOSURE.ordinal());
        this.exposure = exposure;
    }

    public float getExposure() {
        return exposure;
    }

    public void setExposure(float exposure) {
        this.exposure = exposure;
    }
}
