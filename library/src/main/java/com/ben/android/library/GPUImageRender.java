package com.ben.android.library;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;

public class GPUImageRender extends GLSurfaceView {
    static {
        System.loadLibrary("gpuimage");
    }

    public GPUImageRender(Context context) {
        super(context);
    }

    public GPUImageRender(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        int width = 0;
        int height = 0;
        Bitmap bitmap;
        BitmapFactory.Options opts = new BitmapFactory.Options();
        opts.inJustDecodeBounds = true;
        BitmapFactory.decodeResource(getResources(), R.drawable.test, opts);
        width = opts.outWidth;
        height = opts.outHeight;
        bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.test);
        nativeSurfaceCreated(holder.getSurface(),bitmap,width, height);
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
        Log.e("ngp", "surfaceChanged: " + w + h);
        //nativeSurfaceChanged(w, h);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }

    public native void nativeSurfaceCreated(Surface surface, Bitmap bitmap, int width, int height);

    public native void nativeSurfaceChanged(int width, int height);
}
