package com.ben.android.library;

import android.content.Context;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/22
 */
public class GPUImageRender extends SurfaceView implements SurfaceHolder.Callback {

    public GPUImageRender(Context context) {
        super(context);
        init();
    }

    public GPUImageRender(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    private void init() {
        SurfaceHolder holder = getHolder();
        holder.addCallback(this);
    }

    @Override
    public void surfaceCreated(final SurfaceHolder holder) {
        NGPNativeBridge.nativeSurfaceCreated(holder.getSurface());

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, final int w, final int h) {
        NGPNativeBridge.nativeSurfaceChanged(w, h);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        NGPNativeBridge.nativeDestroyed();
    }
}
