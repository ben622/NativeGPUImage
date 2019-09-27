package com.ben.android.library.filter;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/27
 */
public class GPUImage3x3TextureSamplingFilter extends NativeFilter {
    private float texelWidth;
    private float texelHeight;
    private float lineSize = 1.0f;

    public GPUImage3x3TextureSamplingFilter(int filterType) {
        super(filterType);
    }

    public float getTexelWidth() {
        return texelWidth;
    }

    public void setTexelWidth(float texelWidth) {
        this.texelWidth = texelWidth;
    }

    public float getTexelHeight() {
        return texelHeight;
    }

    public void setTexelHeight(float texelHeight) {
        this.texelHeight = texelHeight;
    }

    public float getLineSize() {
        return lineSize;
    }

    public void setLineSize(float lineSize) {
        this.lineSize = lineSize;
    }
}
