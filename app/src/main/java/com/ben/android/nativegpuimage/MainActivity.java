package com.ben.android.nativegpuimage;

import android.content.pm.ActivityInfo;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.opengl.GLUtils;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;

import com.ben.android.library.NGPNativeBridge;
import com.ben.android.library.filter.DilationFilter;
import com.ben.android.library.filter.GaussianBlurFilter;
import com.ben.android.library.filter.PixelationFilter;
import com.ben.android.library.filter.ZoomBlurFilter;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        supportRequestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_main);

    }

    public void setFilter(View view) {
        //NGPNativeBridge.setFilter(new PixelationFilter(110f));
        //NGPNativeBridge.setFilter(new ZoomBlurFilter());
        NGPNativeBridge.setFilter(new DilationFilter(1));

    }

    public void renderBitmap(View view) {
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), com.ben.android.library.R.mipmap.dog);
        Bitmap resizedBitmap = Bitmap.createBitmap(bitmap.getWidth(), bitmap.getHeight(),
                Bitmap.Config.ARGB_8888);
        Canvas can = new Canvas(resizedBitmap);
        can.drawARGB(0x00, 0x00, 0x00, 0x00);
        can.drawBitmap(bitmap, 0, 0, null);

        NGPNativeBridge.setBitmap(resizedBitmap);
    }
}
