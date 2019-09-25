package com.ben.android.library.filter;

import com.ben.android.library.jni.NativeObject;
import com.ben.android.library.jni.annotations.UsedByNativeCode;
import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/21
 */
public class GaussianBlurFilter extends NativeFilter {
    private float blurSize;

    public GaussianBlurFilter() {
        this(10f);
    }

    public GaussianBlurFilter(float blurSize) {
        super(FilterType.GAUSSIAN_BLUR.ordinal());
        this.blurSize = blurSize;
    }

    @SuppressWarnings("UnusedDeclaration")
    @UsedByNativeCode
    public float getBlurSize() {
        return blurSize;
    }

    @SuppressWarnings("UnusedDeclaration")
    @UsedByNativeCode
    public void setBlurSize(float blurSize) {
        this.blurSize = blurSize;
    }
}
