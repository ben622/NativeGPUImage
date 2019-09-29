package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/29
 */
public class GPUImage3x3ConvolutionFilter extends GPUImage3x3TextureSamplingFilter {
    private float v1 = 0.0f;
    private float v2 = 0.0f;
    private float v3 = 0.0f;
    private float v4 = 0.0f;
    private float v5 = 1.0f;
    private float v6 = 0.0f;
    private float v7 = 0.0f;
    private float v8 = 0.0f;
    private float v9 = 0.0f;


    public GPUImage3x3ConvolutionFilter() {
        this(FilterType.THREE_X_THREE_CONVOLUTION.ordinal());
    }
    public GPUImage3x3ConvolutionFilter(int filterType) {
        this(filterType,new float[]{
                0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f});
    }

    public GPUImage3x3ConvolutionFilter(final float[] convolutionKernel) {
        this(FilterType.THREE_X_THREE_CONVOLUTION.ordinal(), convolutionKernel);
    }
    public GPUImage3x3ConvolutionFilter(int filterType,final float[] convolutionKernel) {
        super(filterType);
        if (convolutionKernel == null && convolutionKernel.length < 9) {
            return;
        }
        this.v1 = convolutionKernel[0];
        this.v2 = convolutionKernel[1];
        this.v3 = convolutionKernel[2];
        this.v4 = convolutionKernel[3];
        this.v5 = convolutionKernel[4];
        this.v6 = convolutionKernel[5];
        this.v7 = convolutionKernel[6];
        this.v8 = convolutionKernel[7];
        this.v9 = convolutionKernel[8];
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

    public float getV4() {
        return v4;
    }

    public void setV4(float v4) {
        this.v4 = v4;
    }

    public float getV5() {
        return v5;
    }

    public void setV5(float v5) {
        this.v5 = v5;
    }

    public float getV6() {
        return v6;
    }

    public void setV6(float v6) {
        this.v6 = v6;
    }

    public float getV7() {
        return v7;
    }

    public void setV7(float v7) {
        this.v7 = v7;
    }

    public float getV8() {
        return v8;
    }

    public void setV8(float v8) {
        this.v8 = v8;
    }

    public float getV9() {
        return v9;
    }

    public void setV9(float v9) {
        this.v9 = v9;
    }
}
