package com.ben.android.library.filter;

import android.graphics.PointF;

import com.ben.android.library.jni.annotations.UsedByNativeCode;
import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/24
 */
public class ZoomBlurFilter extends NativeFilter {
    private float pointXF;
    private float pointYF;
    private float blurSize;

    public ZoomBlurFilter() {
        this(null);
    }
    public ZoomBlurFilter(PointF pointF) {
        this(null, 0);
    }
     public ZoomBlurFilter(PointF pointF,int blurSize) {
        super(FilterType.ZOOM_BLUR.ordinal());
        if (pointF != null) {
            this.pointXF = pointF.x;
            this.pointYF = pointF.y;
        }
         this.blurSize = blurSize;
    }


    @SuppressWarnings("UnusedDeclaration")
    @UsedByNativeCode
    public float getPointXF() {
        return pointXF;
    }

    @SuppressWarnings("UnusedDeclaration")
    @UsedByNativeCode
    public void setPointXF(float pointXF) {
        this.pointXF = pointXF;
    }
    @SuppressWarnings("UnusedDeclaration")
    @UsedByNativeCode
    public float getPointYF() {
        return pointYF;
    }

    @SuppressWarnings("UnusedDeclaration")
    @UsedByNativeCode
    public void setPointYF(float pointYF) {
        this.pointYF = pointYF;
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
