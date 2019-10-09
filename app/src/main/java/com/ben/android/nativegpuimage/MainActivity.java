package com.ben.android.nativegpuimage;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

import com.ben.android.library.GPUImageRender;
import com.ben.android.library.NGPNativeBridge;
import com.ben.android.library.filter.GPUImageGrayscaleFilter;

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
//        NGPNativeBridge.nativeApplyFilter(new PixelationFilter(30f));
//        NGPNativeBridge.nativeApplyFilter(new ZoomBlurFilter(new PointF(0.7f,0.7f),1.0f));
//        NGPNativeBridge.nativeApplyFilter(new DilationFilter(1));
//        NGPNativeBridge.nativeApplyFilter(new GaussianBlurFilter(100f));
//        NGPNativeBridge.nativeApplyFilter(new GPUImageWhiteBalanceFilter(1000f,1.0f));
//        NGPNativeBridge.nativeApplyFilter(new GPUImageWeakPixelInclusionFilter());
//        NGPNativeBridge.nativeApplyFilter(new GPUImageVignetteFilter(new PointF(0.5f,0.5f), new float[]{0.0f, 0.0f, 0.0f}, 0.2f, 0.75f));
//        NGPNativeBridge.nativeApplyFilter(new GPUImageVibranceFilter(1.5f));
//        NGPNativeBridge.nativeApplyFilter(new GPUImageAddBlendFilter(BitmapFactory.decodeResource(getResources(), R.drawable.lookup_amatorka)));
//        NGPNativeBridge.nativeApplyFilter(new GPUImageAddBlendFilter(createWatermark("ben622")));
//        NGPNativeBridge.nativeApplyFilter(new GPUImageToonFilter(0.5f,20.0f));
//        NGPNativeBridge.nativeApplyFilter(new GPUImageGammaFilter(2.0f));
//        NGPNativeBridge.nativeApplyFilter(new GPUImageFalseColorFilter());
//        NGPNativeBridge.nativeApplyFilter(new GPUImageExposureFilter());
//        NGPNativeBridge.nativeApplyFilter(new GPUImageExclusionBlendFilter());
//        NGPNativeBridge.nativeApplyFilter(new GPUImage3x3ConvolutionFilter(new float[]{0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f}));
//        NGPNativeBridge.nativeApplyFilter(new GPUImageEmbossFilter());
//        NGPNativeBridge.nativeApplyFilter(new GPUImageDivideBlendFilter(createWatermark("ben622")));
//        NGPNativeBridge.nativeApplyFilter(new GPUImageAlphaBlendFilter(BitmapFactory.decodeResource(getResources(), R.drawable.lookup_amatorka),0.5f));
//        NGPNativeBridge.nativeApplyFilter(new GPUImageDissolveBlendFilter(BitmapFactory.decodeResource(getResources(), R.drawable.lookup_amatorka),1.0f));
//        NGPNativeBridge.nativeApplyFilter(new GPUImageSobelEdgeDetectionFilter(1.7f));
        NGPNativeBridge.nativeApplyFilter(new GPUImageGrayscaleFilter());

        reqeustRender();
    }

    public void renderBitmap(View view) {
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), com.ben.android.library.R.mipmap.dog);
        Bitmap resizedBitmap = Bitmap.createBitmap(bitmap.getWidth(), bitmap.getHeight(),
                Bitmap.Config.ARGB_8888);
        Canvas can = new Canvas(resizedBitmap);
        can.drawARGB(0x00, 0x00, 0x00, 0x00);
        can.drawBitmap(bitmap, 0, 0, null);

        NGPNativeBridge.nativeApplyBitmap(resizedBitmap);
        reqeustRender();
    }

    public void reqeustRender() {
        NGPNativeBridge.nativeRequestRender();
    }

    public void capture(View view) {
        /*int width = gpuImageRender.getMeasuredWidth();
        int height = gpuImageRender.getMeasuredHeight();
        Bitmap resultBitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
        NGPNativeBridge.nativeCapture(resultBitmap);
        //show
        ImageView imageView = new ImageView(this);
        imageView.setImageBitmap(resultBitmap);
        new AlertDialog.Builder(this)
                .setView(imageView)
                .create().show();*/

        NGPNativeBridge.nativeCreateGL();

    }

    public Bitmap createWatermark(String value) {
        Bitmap bitmap = Bitmap.createBitmap(100, 100, Bitmap.Config.ARGB_8888);
        Canvas canvas = new Canvas(bitmap);
        Paint paint = new Paint(Paint.ANTI_ALIAS_FLAG);
        paint.setColor(Color.WHITE);
        paint.setTextSize(20);
        canvas.drawText(value, 30, 30, paint);
        return bitmap;
    }
}
