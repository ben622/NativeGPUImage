package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/8
 */
public class GPUImageCrosshatchFilter extends NativeFilter {
    private float crossHatchSpacing;
    private float lineWidth;

    public GPUImageCrosshatchFilter() {
        this(0.03f, 0.003f);
    }

    public GPUImageCrosshatchFilter(float crossHatchSpacing, float lineWidth) {
        super(FilterType.CROSSHATCH.ordinal());
        this.crossHatchSpacing = crossHatchSpacing;
        this.lineWidth = lineWidth;
    }

    public float getCrossHatchSpacing() {
        return crossHatchSpacing;
    }

    public void setCrossHatchSpacing(float crossHatchSpacing) {
        this.crossHatchSpacing = crossHatchSpacing;
    }

    public float getLineWidth() {
        return lineWidth;
    }

    public void setLineWidth(float lineWidth) {
        this.lineWidth = lineWidth;
    }
}
