package com.ben.android.library;

import android.content.Context;
import android.graphics.BitmapFactory;
import android.util.AttributeSet;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.widget.FrameLayout;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/22
 */
public class NGPSurfaceView extends FrameLayout implements SurfaceHolder.Callback {
    protected SurfaceView mSurfaceView;
    protected boolean isCreteGL = false;
    private OnEGPEnvironmentListener onEGPEnvironmentListener;

    public void setOnEGPEnvironmentListener(OnEGPEnvironmentListener onEGPEnvironmentListener) {
        this.onEGPEnvironmentListener = onEGPEnvironmentListener;
    }

    public NGPSurfaceView(Context context) {
        super(context);
    }

    public NGPSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);

    }

    public void initialize(){
        mSurfaceView = new SurfaceView(getContext());
        this.addView(mSurfaceView);
        mSurfaceView.getHolder().addCallback(this);
    }

    @Override
    public void surfaceCreated(final SurfaceHolder holder) {
        NGPNativeBridge.nativeSurfaceCreated(holder.getSurface());
        isCreteGL = true;
        if (onEGPEnvironmentListener!=null) onEGPEnvironmentListener.onCreateEGLFinish();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, final int w, final int h) {
        NGPNativeBridge.nativeSurfaceChanged(w, h);
        NGPNativeBridge.nativeRequestRender();
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        NGPNativeBridge.nativeDestorySurfaceGL();
    }
}
