package com.ben.android.nativegpuimage;

import android.content.pm.ActivityInfo;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.opengl.GLUtils;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ImageView;

import com.ben.android.library.GPUImageRender;
import com.ben.android.library.NGPNativeBridge;
import com.ben.android.library.filter.DilationFilter;
import com.ben.android.library.filter.GPUImageVignetteFilter;
import com.ben.android.library.filter.GPUImageWeakPixelInclusionFilter;
import com.ben.android.library.filter.GPUImageWhiteBalanceFilter;
import com.ben.android.library.filter.GaussianBlurFilter;
import com.ben.android.library.filter.PixelationFilter;
import com.ben.android.library.filter.ZoomBlurFilter;

public class MainActivity extends AppCompatActivity {
    private GPUImageRender gpuImageRender;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        gpuImageRender = findViewById(R.id.mGPUImageRender);
        NGPNativeBridge.init();

    }

    public void setFilter(View view) {
        //NGPNativeBridge.setFilter(new PixelationFilter(110f));
//        NGPNativeBridge.setFilter(new ZoomBlurFilter());
        NGPNativeBridge.setFilter(new DilationFilter(1));
        //NGPNativeBridge.setFilter(new GaussianBlurFilter(10));
        //NGPNativeBridge.setFilter(new GPUImageWhiteBalanceFilter());
//        NGPNativeBridge.setFilter(new GPUImageWeakPixelInclusionFilter());
//        NGPNativeBridge.setFilter(new GPUImageVignetteFilter());


        reqeustRender();
    }

    public void renderBitmap(View view) {
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), com.ben.android.library.R.mipmap.dog);
        Bitmap resizedBitmap = Bitmap.createBitmap(bitmap.getWidth(), bitmap.getHeight(),
                Bitmap.Config.ARGB_8888);
        Canvas can = new Canvas(resizedBitmap);
        can.drawARGB(0x00, 0x00, 0x00, 0x00);
        can.drawBitmap(bitmap, 0, 0, null);

        NGPNativeBridge.setBitmap(resizedBitmap);
        reqeustRender();
    }

    public void reqeustRender() {
        NGPNativeBridge.requestRender();
    }

    public void capture(View view) {
        int width = gpuImageRender.getMeasuredWidth();
        int height = gpuImageRender.getMeasuredHeight();
        Bitmap resultBitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
        NGPNativeBridge.capture(resultBitmap);
        //show
        ImageView imageView = new ImageView(this);
        imageView.setImageBitmap(resultBitmap);
        new AlertDialog.Builder(this)
                .setView(imageView)
                .create().show();

    }
}
