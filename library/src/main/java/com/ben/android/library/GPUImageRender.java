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
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.dog);
        Bitmap resizedBitmap = Bitmap.createBitmap(bitmap.getWidth(), bitmap.getHeight(),
                Bitmap.Config.ARGB_8888);
        Canvas can = new Canvas(resizedBitmap);
        can.drawARGB(0x00, 0x00, 0x00, 0x00);
        can.drawBitmap(bitmap, 0, 0, null);
        nativeSurfaceCreated(holder.getSurface(), resizedBitmap, resizedBitmap.getWidth(), resizedBitmap.getHeight());

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, final int w, final int h) {
  /*      int width = 0;
        int height = 0;
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.test);
        Bitmap resizedBitmap = Bitmap.createBitmap(bitmap.getWidth(), bitmap.getHeight(),
                Bitmap.Config.ARGB_8888);
        Canvas can = new Canvas(resizedBitmap);
        can.drawARGB(0x00, 0x00, 0x00, 0x00);
        can.drawBitmap(bitmap, 0, 0, null);

        nativeSurfaceChanged(resizedBitmap, resizedBitmap.getWidth(), resizedBitmap.getHeight(), w, h);*/
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }

    public native void nativeSurfaceCreated(Surface surface, Bitmap bitmap, int imageWidth, int imageHeight);

    public native void nativeSurfaceChanged(Bitmap bitmap, int imageWidth, int imageHeight, int width, int height);
}
