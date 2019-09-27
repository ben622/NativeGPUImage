package com.ben.android.library.filter;

import android.graphics.PointF;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/27
 */
public class GPUImageVignetteFilter extends NativeFilter {
    private float vignetteCenterX;
    private float vignetteCenterY;
    private float[] vignetteColor;
    private float vignetteStart;
    private float vignetteEnd;

    public GPUImageVignetteFilter() {
        this(new PointF(), new float[]{0.0f, 0.0f, 0.0f}, 0.3f, 0.75f);
    }

    public GPUImageVignetteFilter(PointF vignetteCenter, float[] vignetteColor, float vignetteStart, float vignetteEnd) {
        super(FilterType.VIGNETTE.ordinal());
        this.vignetteCenterX = vignetteCenter.x;
        this.vignetteCenterY = vignetteCenter.y;
        this.vignetteColor = vignetteColor;
        this.vignetteStart = vignetteStart;
        this.vignetteEnd = vignetteEnd;
    }

    public float getVignetteCenterX() {
        return vignetteCenterX;
    }

    public void setVignetteCenterX(float vignetteCenterX) {
        this.vignetteCenterX = vignetteCenterX;
    }

    public float getVignetteCenterY() {
        return vignetteCenterY;
    }

    public void setVignetteCenterY(float vignetteCenterY) {
        this.vignetteCenterY = vignetteCenterY;
    }

    public float[] getVignetteColor() {
        return vignetteColor;
    }

    public void setVignetteColor(float[] vignetteColor) {
        this.vignetteColor = vignetteColor;
    }

    public float getVignetteStart() {
        return vignetteStart;
    }

    public void setVignetteStart(float vignetteStart) {
        this.vignetteStart = vignetteStart;
    }

    public float getVignetteEnd() {
        return vignetteEnd;
    }

    public void setVignetteEnd(float vignetteEnd) {
        this.vignetteEnd = vignetteEnd;
    }
}
