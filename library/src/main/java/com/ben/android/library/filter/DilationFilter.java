package com.ben.android.library.filter;

import android.support.annotation.IntRange;

import com.ben.android.library.jni.annotations.UsedByNativeCode;
import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/24
 */
public class DilationFilter extends NativeFilter {
    /**
     * Acceptable values for dilationRadius, which sets the distance in pixels to sample out from the center,
     * are 1, 2, 3, and 4.
     */
    private int radius;

    @SuppressWarnings("UnusedDeclaration")
    @UsedByNativeCode
    public int getRadius() {
        return radius;
    }
    @SuppressWarnings("UnusedDeclaration")
    @UsedByNativeCode
    public void setRadius(@IntRange(from = 1,to = 4) int radius) {
        this.radius = radius;
    }

    public DilationFilter() {
        this(1);
    }

    public DilationFilter(int radius) {
        super(FilterType.DILATION.ordinal());
        this.radius = radius;
    }
}
