package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/29
 */
public class GPUImageFalseColorFilter extends NativeFilter {
    private float firstRed, firstGreen, firstBlue, secondRed, secondGreen, secondBlue;

    public GPUImageFalseColorFilter() {
        this(0f, 0f, 0.5f, 1f, 0f, 0f);
    }

    public GPUImageFalseColorFilter(float firstRed, float firstGreen, float firstBlue, float secondRed, float secondGreen, float secondBlue) {
        super(FilterType.FALSE_COLOR.ordinal());
        this.firstRed = firstRed;
        this.firstGreen = firstGreen;
        this.firstBlue = firstBlue;
        this.secondRed = secondRed;
        this.secondGreen = secondGreen;
        this.secondBlue = secondBlue;
    }

    public float getFirstRed() {
        return firstRed;
    }

    public void setFirstRed(float firstRed) {
        this.firstRed = firstRed;
    }

    public float getFirstGreen() {
        return firstGreen;
    }

    public void setFirstGreen(float firstGreen) {
        this.firstGreen = firstGreen;
    }

    public float getFirstBlue() {
        return firstBlue;
    }

    public void setFirstBlue(float firstBlue) {
        this.firstBlue = firstBlue;
    }

    public float getSecondRed() {
        return secondRed;
    }

    public void setSecondRed(float secondRed) {
        this.secondRed = secondRed;
    }

    public float getSecondGreen() {
        return secondGreen;
    }

    public void setSecondGreen(float secondGreen) {
        this.secondGreen = secondGreen;
    }

    public float getSecondBlue() {
        return secondBlue;
    }

    public void setSecondBlue(float secondBlue) {
        this.secondBlue = secondBlue;
    }
}
