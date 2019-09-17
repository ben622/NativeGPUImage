package com.ben.android.library;

import android.content.Context;
import android.graphics.Bitmap;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.Surface;
import android.view.SurfaceHolder;

public class GPUImageRender extends GLSurfaceView {

    public GPUImageRender(Context context) {
        super(context);
    }

    public GPUImageRender(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        super.surfaceCreated(holder);
        nativeSurfaceCreated(holder.getSurface(),null,0,0);
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
        super.surfaceChanged(holder, format, w, h);
        nativeSurfaceChanged(w, h);
    }



    public native void nativeSurfaceCreated(Surface surface, Bitmap bitmap,int width, int height);

    public native void nativeSurfaceChanged(int width, int height);
}
