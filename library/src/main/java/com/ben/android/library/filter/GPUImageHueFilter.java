package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/8
 */
public class GPUImageHueFilter extends NativeFilter {
    private float hue;

    public GPUImageHueFilter() {
        this(90.0f);
    }

    public GPUImageHueFilter(float hue) {
        super(FilterType.HUE.ordinal());
        this.hue = hue;
    }

    public float getHue() {
        return hue;
    }

    public void setHue(float hue) {
        this.hue = hue;
    }
}
