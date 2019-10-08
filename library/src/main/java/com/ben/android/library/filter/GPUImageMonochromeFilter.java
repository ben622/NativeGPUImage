package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/8
 */
public class GPUImageMonochromeFilter extends NativeFilter {
    private float intensity;
    private float v1,v2, v3;
    public GPUImageMonochromeFilter() {
        this(1.0f, new float[]{0.6f, 0.45f, 0.3f, 1.0f});
    }

    public GPUImageMonochromeFilter(float intensity) {
        this(intensity, new float[]{0.6f, 0.45f, 0.3f, 1.0f});
    }

    /**
     * @param intensity
     * @param color color[0] is red,color[1] is green,color[2] is blue.
     */
    public GPUImageMonochromeFilter(final float intensity, final float[] color) {
        super(FilterType.MONOCHROME.ordinal());
        this.intensity = intensity;
        if (color != null && color.length == 3) {
            this.v1 = color[0];
            this.v2 = color[1];
            this.v3 = color[2];
        }
    }

    public float getIntensity() {
        return intensity;
    }

    public void setIntensity(float intensity) {
        this.intensity = intensity;
    }

    public float getV1() {
        return v1;
    }

    public void setV1(float v1) {
        this.v1 = v1;
    }

    public float getV2() {
        return v2;
    }

    public void setV2(float v2) {
        this.v2 = v2;
    }

    public float getV3() {
        return v3;
    }

    public void setV3(float v3) {
        this.v3 = v3;
    }
}
