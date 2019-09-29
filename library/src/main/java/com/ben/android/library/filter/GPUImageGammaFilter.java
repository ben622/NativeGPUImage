package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/29
 */
public class GPUImageGammaFilter extends NativeFilter {
    private float gamma;

    public GPUImageGammaFilter() {
        this(1.2f);
    }
    public GPUImageGammaFilter(float gamma) {
        super(FilterType.GAMMA.ordinal());
        this.gamma = gamma;
    }

    public float getGamma() {
        return gamma;
    }

    public void setGamma(float gamma) {
        this.gamma = gamma;
    }
}
