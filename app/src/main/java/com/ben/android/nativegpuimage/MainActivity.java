package com.ben.android.nativegpuimage;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

import com.ben.android.library.GPUImageRender;
import com.ben.android.library.NGP;
import com.ben.android.library.NGPNativeBridge;
import com.ben.android.library.filter.GPUImageGrayscaleFilter;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        NGP.initialize(this);

    }

    public void fboTest(View view) {
        startActivity(new Intent(this, ImageActivity.class));
    }
}
