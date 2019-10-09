package com.ben.android.nativegpuimage;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;

import com.ben.android.library.NGP;
import com.ben.android.library.NGPNativeBridge;
import com.ben.android.library.filter.GPUImageThresholdEdgeDetectionFilter;

public class FBOActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fbo);

    }

    public void OnClick(View view) {
        NGPNativeBridge.init();
        NGPNativeBridge.nativeCreateGL();
        NGPNativeBridge.nativeSurfaceChanged(1080, 1920);
        NGPNativeBridge.nativeApplyFilter(new GPUImageThresholdEdgeDetectionFilter());

        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), com.ben.android.library.R.mipmap.dog);
        Bitmap resizedBitmap = Bitmap.createBitmap(bitmap.getWidth(), bitmap.getHeight(),
                Bitmap.Config.ARGB_8888);
        Canvas can = new Canvas(resizedBitmap);
        can.drawARGB(0x00, 0x00, 0x00, 0x00);
        can.drawBitmap(bitmap, 0, 0, null);
        NGPNativeBridge.nativeApplyBitmap(bitmap);

        Bitmap resultBitmap = Bitmap.createBitmap(1080, 1920, Bitmap.Config.ARGB_8888);
        long start = System.currentTimeMillis();
        NGPNativeBridge.nativeCapture(resultBitmap);
        long end = System.currentTimeMillis();
        Log.e("ngp", "OnClick: " + (end - start));
        //show
        ImageView imageView = new ImageView(this);
        imageView.setImageBitmap(resultBitmap);
        new AlertDialog.Builder(this)
                .setView(imageView)
                .create().show();


        NGP.with(this)
                .applyBitmapByUrls("http://www.baidu.com/log.png")
                .applyFilter(new GPUImageThresholdEdgeDetectionFilter())
                .into(imageView);



    }
}
