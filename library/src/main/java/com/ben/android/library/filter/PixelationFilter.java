package com.ben.android.library.filter;

import com.ben.android.library.jni.annotations.UsedByNativeCode;
import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/24
 */
public class PixelationFilter extends NativeFilter{
    private float pixel;

    @SuppressWarnings("UnusedDeclaration")
    @UsedByNativeCode
    public float getPixel() {
        return pixel;
    }
    @SuppressWarnings("UnusedDeclaration")
    @UsedByNativeCode
    public void setPixel(float pixel) {
        this.pixel = pixel;
    }
    public PixelationFilter() {
        this(1.0f);
    }

    public PixelationFilter(float pixel) {
        super(FilterType.PIXELATION.ordinal());
        this.pixel = pixel;
    }
}
