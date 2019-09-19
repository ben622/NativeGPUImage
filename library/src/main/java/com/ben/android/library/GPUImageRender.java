package com.ben.android.library;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
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
        new Thread(new Runnable() {

            @Override
            public void run() {
                Log.e("ngp", "surfaceCreated: ");
                nativeSurfaceCreated(holder.getSurface());
            }
        }).start();

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, final int w, final int h) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                int width = 0;
                int height = 0;
                Bitmap bitmap;
                BitmapFactory.Options opts = new BitmapFactory.Options();
                opts.inJustDecodeBounds = true;
                BitmapFactory.decodeResource(getResources(), R.drawable.test, opts);
                width = opts.outWidth;
                height = opts.outHeight;
                bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.test);

                Log.e("ngp", "surfaceChanged: " + w + h);
                nativeSurfaceChanged(bitmap,width,height,w, h);
            }
        }).start();

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }

    public native void nativeSurfaceCreated(Surface surface);

    public native void nativeSurfaceChanged(Bitmap bitmap,int imageWidth,int imageHeight,int width, int height);
}
