package com.ben.android.nativegpuimage;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

import com.ben.android.library.NGP;

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

    public void showRenderBitmap(View view) {
        startActivity(new Intent(this, ShowBitmapActivity.class));
    }
}
