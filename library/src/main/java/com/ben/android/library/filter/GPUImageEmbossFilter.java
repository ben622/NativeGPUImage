package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/29
 */
public class GPUImageEmbossFilter extends GPUImage3x3ConvolutionFilter {
    private float intensity;

    public GPUImageEmbossFilter() {
        this(1.0f);
    }

    public GPUImageEmbossFilter(float intensity) {
        super(FilterType.EMBOSS.ordinal());
        this.intensity = intensity;
    }

    public float getIntensity() {
        return intensity;
    }

    public void setIntensity(float intensity) {
        this.intensity = intensity;
    }
}
