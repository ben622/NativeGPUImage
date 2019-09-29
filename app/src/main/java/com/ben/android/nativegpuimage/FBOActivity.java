package com.ben.android.nativegpuimage;

import android.graphics.Bitmap;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

import com.ben.android.library.NGPNativeBridge;
import com.ben.android.library.filter.PixelationFilter;

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
        //NGPNativeBridge.setFilter(new PixelationFilter(30f));
        //NGPNativeBridge.requestRender();

        Bitmap resultBitmap = Bitmap.createBitmap(1080, 1920, Bitmap.Config.ARGB_8888);
        NGPNativeBridge.capture(resultBitmap);
        //show
        ImageView imageView = new ImageView(this);
        imageView.setImageBitmap(resultBitmap);
        new AlertDialog.Builder(this)
                .setView(imageView)
                .create().show();
    }
}
