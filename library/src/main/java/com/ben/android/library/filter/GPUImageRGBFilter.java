package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/8
 */
public class GPUImageRGBFilter extends NativeFilter {
    private float red;
    private float green;
    private float blue;

    public GPUImageRGBFilter() {
        this(1.0f, 1.0f, 1.0f);
    }

    public GPUImageRGBFilter(float red, float green, float blue) {
        super(FilterType.RGB.ordinal());
        this.red = red;
        this.green = green;
        this.blue = blue;
    }

    public float getRed() {
        return red;
    }

    public void setRed(float red) {
        this.red = red;
    }

    public float getGreen() {
        return green;
    }

    public void setGreen(float green) {
        this.green = green;
    }

    public float getBlue() {
        return blue;
    }

    public void setBlue(float blue) {
        this.blue = blue;
    }
}
