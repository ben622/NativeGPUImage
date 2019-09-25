package com.ben.android.library;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class GPUImageRender extends SurfaceView implements SurfaceHolder.Callback {
    static {
        System.loadLibrary("gpuimage");
    }

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
        holder.setFormat(PixelFormat.RGBA_8888);
        holder.addCallback(this);
    }

    @Override
    public void surfaceCreated(final SurfaceHolder holder) {
        nativeSurfaceCreated(holder.getSurface());

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, final int w, final int h) {
        nativeSurfaceChanged(w, h);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }


    public native void nativeSurfaceCreated(Surface surface);

    public native void nativeSurfaceChanged(int width, int height);

    public native void nativeSurfaceDestroyed();
}
