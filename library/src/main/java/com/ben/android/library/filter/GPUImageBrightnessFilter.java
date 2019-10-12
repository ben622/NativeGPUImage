package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/8
 */
public class GPUImageBrightnessFilter extends NativeFilter {
    private float brightness;

    public GPUImageBrightnessFilter() {
        this(0.0f);
    }

    public GPUImageBrightnessFilter(float brightness) {
        super(FilterType.BRIGHTNESS.ordinal());
        this.brightness = brightness;
    }

    public float getBrightness() {
        return brightness;
    }

    public void setBrightness(float brightness) {
        this.brightness = brightness;
    }

    @Override
    public String toString() {
        return "GPUImageBrightnessFilter{" +
                "brightness=" + brightness +
                '}';
    }
}
