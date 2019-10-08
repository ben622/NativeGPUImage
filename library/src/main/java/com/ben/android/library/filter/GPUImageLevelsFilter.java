package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/8
 */
public class GPUImageLevelsFilter extends NativeFilter {
    private float minV1 = 0.0f;
    private float minV2 = 0.0f;
    private float minV3 = 0.0f;
    private float midV1 = 1.0f;
    private float midV2 = 1.0f;
    private float midV3 = 1.0f;
    private float maxV1 = 1.0f;
    private float maxV2 = 1.0f;
    private float maxV3 = 1.0f;
    private float minOutputV1 = 0.0f;
    private float minOutputV2 = 0.0f;
    private float minOutputV3 = 0.0f;
    private float maxOutputV1 = 1.0f;
    private float maxOutputV2 = 1.0f;
    private float maxOutputV3 = 1.0f;

    private float min = 0.0f;
    private float mid = 0.5f;
    private float max = 1.0f;
    private float minOut = 0.0f;
    private float maxOut = 1.0f;

    public GPUImageLevelsFilter() {
        this(
                new float[]{0.0f, 0.0f, 0.0f},
                new float[]{1.0f, 1.0f, 1.0f},
                new float[]{1.0f, 1.0f, 1.0f},
                new float[]{0.0f, 0.0f, 0.0f},
                new float[]{1.0f, 1.0f, 1.0f},
                0.0f, 0.5f, 1.0f, 0.0f, 1.0f);
    }

    public GPUImageLevelsFilter(float min, float mid, float max, float minOut, float maxOut) {
        this(
                new float[]{0.0f, 0.0f, 0.0f},
                new float[]{1.0f, 1.0f, 1.0f},
                new float[]{1.0f, 1.0f, 1.0f},
                new float[]{0.0f, 0.0f, 0.0f},
                new float[]{1.0f, 1.0f, 1.0f},
                min, mid, max, minOut, maxOut);

    }

    public GPUImageLevelsFilter(float min, float mid, float max) {
        this(
                new float[]{0.0f, 0.0f, 0.0f},
                new float[]{1.0f, 1.0f, 1.0f},
                new float[]{1.0f, 1.0f, 1.0f},
                new float[]{0.0f, 0.0f, 0.0f},
                new float[]{1.0f, 1.0f, 1.0f},
                min, mid, max, 0.0f, 1.0f);
    }

    public GPUImageLevelsFilter(final float[] min, final float[] mid, final float[] max, final float[] minOUt, final float[] maxOut,
                                 float nMin, float nMid, float nMax, float nMinOut,
                                 float nMaxOut) {
        super(FilterType.LEVELS_FILTER_MIN.ordinal());
        this.min = nMin;
        this.mid = nMid;
        this.max = nMax;
        this.minOut = nMinOut;
        this.maxOut = nMaxOut;

        minV1 = min[0];
        minV2 = min[1];
        minV3 = min[2];

        midV1 = mid[0];
        midV2 = mid[1];
        midV3 = mid[2];

        maxV1 = max[0];
        maxV2 = max[1];
        maxV3 = max[2];

        minOutputV1 = minOUt[0];
        minOutputV2 = minOUt[1];
        minOutputV3 = minOUt[2];

        maxOutputV1 = maxOut[0];
        maxOutputV2 = maxOut[1];
        maxOutputV3 = maxOut[2];
    }

    public float getMinV1() {
        return minV1;
    }

    public void setMinV1(float minV1) {
        this.minV1 = minV1;
    }

    public float getMinV2() {
        return minV2;
    }

    public void setMinV2(float minV2) {
        this.minV2 = minV2;
    }

    public float getMinV3() {
        return minV3;
    }

    public void setMinV3(float minV3) {
        this.minV3 = minV3;
    }

    public float getMidV1() {
        return midV1;
    }

    public void setMidV1(float midV1) {
        this.midV1 = midV1;
    }

    public float getMidV2() {
        return midV2;
    }

    public void setMidV2(float midV2) {
        this.midV2 = midV2;
    }

    public float getMidV3() {
        return midV3;
    }

    public void setMidV3(float midV3) {
        this.midV3 = midV3;
    }

    public float getMaxV1() {
        return maxV1;
    }

    public void setMaxV1(float maxV1) {
        this.maxV1 = maxV1;
    }

    public float getMaxV2() {
        return maxV2;
    }

    public void setMaxV2(float maxV2) {
        this.maxV2 = maxV2;
    }

    public float getMaxV3() {
        return maxV3;
    }

    public void setMaxV3(float maxV3) {
        this.maxV3 = maxV3;
    }

    public float getMinOutputV1() {
        return minOutputV1;
    }

    public void setMinOutputV1(float minOutputV1) {
        this.minOutputV1 = minOutputV1;
    }

    public float getMinOutputV2() {
        return minOutputV2;
    }

    public void setMinOutputV2(float minOutputV2) {
        this.minOutputV2 = minOutputV2;
    }

    public float getMinOutputV3() {
        return minOutputV3;
    }

    public void setMinOutputV3(float minOutputV3) {
        this.minOutputV3 = minOutputV3;
    }

    public float getMaxOutputV1() {
        return maxOutputV1;
    }

    public void setMaxOutputV1(float maxOutputV1) {
        this.maxOutputV1 = maxOutputV1;
    }

    public float getMaxOutputV2() {
        return maxOutputV2;
    }

    public void setMaxOutputV2(float maxOutputV2) {
        this.maxOutputV2 = maxOutputV2;
    }

    public float getMaxOutputV3() {
        return maxOutputV3;
    }

    public void setMaxOutputV3(float maxOutputV3) {
        this.maxOutputV3 = maxOutputV3;
    }

    public float getMin() {
        return min;
    }

    public void setMin(float min) {
        this.min = min;
    }

    public float getMid() {
        return mid;
    }

    public void setMid(float mid) {
        this.mid = mid;
    }

    public float getMax() {
        return max;
    }

    public void setMax(float max) {
        this.max = max;
    }

    public float getMinOut() {
        return minOut;
    }

    public void setMinOut(float minOut) {
        this.minOut = minOut;
    }

    public float getMaxOut() {
        return maxOut;
    }

    public void setMaxOut(float maxOut) {
        this.maxOut = maxOut;
    }
}
