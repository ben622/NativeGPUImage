package com.ben.android.nativegpuimage;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.PointF;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;

import com.ben.android.library.NGP;
import com.ben.android.library.NGPFilterListener;
import com.ben.android.library.NGPNativeBridge;
import com.ben.android.library.Result;
import com.ben.android.library.filter.DilationFilter;
import com.ben.android.library.filter.GPUImage3x3ConvolutionFilter;
import com.ben.android.library.filter.GPUImageAddBlendFilter;
import com.ben.android.library.filter.GPUImageAlphaBlendFilter;
import com.ben.android.library.filter.GPUImageBrightnessFilter;
import com.ben.android.library.filter.GPUImageContrastFilter;
import com.ben.android.library.filter.GPUImageCrosshatchFilter;
import com.ben.android.library.filter.GPUImageDissolveBlendFilter;
import com.ben.android.library.filter.GPUImageDivideBlendFilter;
import com.ben.android.library.filter.GPUImageEmbossFilter;
import com.ben.android.library.filter.GPUImageExclusionBlendFilter;
import com.ben.android.library.filter.GPUImageExposureFilter;
import com.ben.android.library.filter.GPUImageFalseColorFilter;
import com.ben.android.library.filter.GPUImageGammaFilter;
import com.ben.android.library.filter.GPUImageGrayscaleFilter;
import com.ben.android.library.filter.GPUImageHalftoneFilter;
import com.ben.android.library.filter.GPUImageHazeFilter;
import com.ben.android.library.filter.GPUImageHighlightShadowFilter;
import com.ben.android.library.filter.GPUImageHueFilter;
import com.ben.android.library.filter.GPUImageLevelsFilter;
import com.ben.android.library.filter.GPUImageLuminanceFilter;
import com.ben.android.library.filter.GPUImageLuminanceThresholdFilter;
import com.ben.android.library.filter.GPUImageMonochromeFilter;
import com.ben.android.library.filter.GPUImageRGBDilationFilter;
import com.ben.android.library.filter.GPUImageRGBFilter;
import com.ben.android.library.filter.GPUImageSaturationFilter;
import com.ben.android.library.filter.GPUImageSharpenFilter;
import com.ben.android.library.filter.GPUImageSketchFilter;
import com.ben.android.library.filter.GPUImageSobelEdgeDetectionFilter;
import com.ben.android.library.filter.GPUImageSolarizeFilter;
import com.ben.android.library.filter.GPUImageThresholdEdgeDetectionFilter;
import com.ben.android.library.filter.GPUImageToonFilter;
import com.ben.android.library.filter.GPUImageVibranceFilter;
import com.ben.android.library.filter.GPUImageVignetteFilter;
import com.ben.android.library.filter.GPUImageWeakPixelInclusionFilter;
import com.ben.android.library.filter.GPUImageWhiteBalanceFilter;
import com.ben.android.library.filter.GaussianBlurFilter;
import com.ben.android.library.filter.NativeFilter;
import com.ben.android.library.filter.PixelationFilter;
import com.ben.android.library.filter.ZoomBlurFilter;
import com.ben.android.library.render.Render;
import com.ben.android.library.util.Rotation;
import com.ben.android.library.util.ScaleType;

import java.util.ArrayList;
import java.util.List;

public class FBOActivity extends AppCompatActivity {

    private String TAG = this.getClass().getSimpleName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fbo);
    }

    public void OnClick(View view) {
        NGP.initialize(this);

        final ImageView imageView = new ImageView(this);
       /* new AlertDialog.Builder(this)
                .setView(imageView)
                .create().show();*/
        final List<NativeFilter> filters = new ArrayList<NativeFilter>() {
            {
               /* add(new GPUImageSketchFilter());
                add(new GPUImageThresholdEdgeDetectionFilter());
                add(new GPUImageCrosshatchFilter());
                add(new GPUImageHalftoneFilter());
                add(new GPUImageLuminanceThresholdFilter());*/
                add(new GPUImageLuminanceFilter());
                add(new GPUImageSolarizeFilter(0.01f));
                add(new GPUImageHazeFilter());
                add(new GPUImageHighlightShadowFilter(0.5f, 0.5f));
                add(new GPUImageSharpenFilter(-4.0f));
                add(new GPUImageMonochromeFilter(0.5f));
                add(new GPUImageHueFilter(50f));
                add(new GPUImageRGBDilationFilter(3));
                add(new GPUImageRGBFilter(1.0f, 0.5f, 0.5f));
                add(new GPUImageLevelsFilter(0.0f, 0.3f, 1.0f));
                add(new GPUImageBrightnessFilter(0.5f));
                add(new GPUImageContrastFilter(2.0f));
                add(new GPUImageSaturationFilter(2.0f));
                add(new PixelationFilter(30f));
                add(new ZoomBlurFilter(new PointF(0.7f, 0.7f), 1.0f));
                add(new DilationFilter(1));
                add(new GaussianBlurFilter(10f));
                add(new GPUImageWhiteBalanceFilter(1000f, 1.0f));
                add(new GPUImageWeakPixelInclusionFilter());
                add(new GPUImageVignetteFilter(new PointF(0.5f, 0.5f), new float[]{0.0f, 0.0f, 0.0f}, 0.2f, 0.75f));
                add(new GPUImageSobelEdgeDetectionFilter(1.7f));
                add(new GPUImageGrayscaleFilter());
                add(new GPUImageVibranceFilter(1.5f));
                add(new GPUImageAddBlendFilter(BitmapFactory.decodeResource(getResources(), R.drawable.lookup_amatorka)));
                add(new GPUImageAddBlendFilter(BitmapFactory.decodeResource(getResources(), R.drawable.lookup_amatorka)));
                add(new GPUImageToonFilter(0.5f, 20.0f));
                add(new GPUImageGammaFilter(2.0f));
                add(new GPUImageFalseColorFilter());
                add(new GPUImageExposureFilter());
                add(new GPUImageExclusionBlendFilter());
                add(new GPUImage3x3ConvolutionFilter(new float[]{0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f}));
                add(new GPUImageEmbossFilter());
                add(new GPUImageDivideBlendFilter(BitmapFactory.decodeResource(getResources(), R.drawable.lookup_amatorka)));
                add(new GPUImageAlphaBlendFilter(BitmapFactory.decodeResource(getResources(), R.drawable.lookup_amatorka), 0.5f));
                add(new GPUImageDissolveBlendFilter(BitmapFactory.decodeResource(getResources(), R.drawable.lookup_amatorka), 1.0f));
            }
        };
       new Thread(new Runnable() {
           @Override
           public void run() {


               List<Result> results = NGP.with(FBOActivity.this)
                       .applyBitmapByUrls(
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg"
                       )
                       .applyFilter(new GPUImageSaturationFilter(2.0f))
                       //.applyWidth(1000)   //指定宽度渲染，不指定宽度则按原图宽度渲染
                       //.applyHeight(1000)  //指定高度渲染，不指定高度则按原图高度渲染
                       .applyRotation(Rotation.ROTATION_90)
                       .applyScaleType(ScaleType.CENTER_CROP)
                       .applyNGPFilter(new NGPFilterListener() {
                           @Override
                           public Render.UpgradRender apply(Render.UpgradRender render, int position) {
                               //针对批量处理单独设置filter
                               render.setFilter(filters.get(position));
                               return render;
                           }
                       })
                       .build()
                       .get();

               for (Result result : results) {
                   Log.e(TAG, "run: "+result.getPath() );
               }

           }
       }).start();


    }
}
