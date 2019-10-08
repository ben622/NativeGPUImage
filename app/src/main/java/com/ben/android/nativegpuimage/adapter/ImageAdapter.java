package com.ben.android.nativegpuimage.adapter;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.PointF;
import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;

import com.ben.android.library.NGPNativeBridge;
import com.ben.android.library.filter.DilationFilter;
import com.ben.android.library.filter.GPUImage3x3ConvolutionFilter;
import com.ben.android.library.filter.GPUImageAddBlendFilter;
import com.ben.android.library.filter.GPUImageAlphaBlendFilter;
import com.ben.android.library.filter.GPUImageBrightnessFilter;
import com.ben.android.library.filter.GPUImageContrastFilter;
import com.ben.android.library.filter.GPUImageDissolveBlendFilter;
import com.ben.android.library.filter.GPUImageDivideBlendFilter;
import com.ben.android.library.filter.GPUImageEmbossFilter;
import com.ben.android.library.filter.GPUImageExclusionBlendFilter;
import com.ben.android.library.filter.GPUImageExposureFilter;
import com.ben.android.library.filter.GPUImageFalseColorFilter;
import com.ben.android.library.filter.GPUImageGammaFilter;
import com.ben.android.library.filter.GPUImageGrayscaleFilter;
import com.ben.android.library.filter.GPUImageHazeFilter;
import com.ben.android.library.filter.GPUImageHighlightShadowFilter;
import com.ben.android.library.filter.GPUImageHueFilter;
import com.ben.android.library.filter.GPUImageLevelsFilter;
import com.ben.android.library.filter.GPUImageMonochromeFilter;
import com.ben.android.library.filter.GPUImageRGBDilationFilter;
import com.ben.android.library.filter.GPUImageRGBFilter;
import com.ben.android.library.filter.GPUImageSaturationFilter;
import com.ben.android.library.filter.GPUImageSharpenFilter;
import com.ben.android.library.filter.GPUImageSobelEdgeDetectionFilter;
import com.ben.android.library.filter.GPUImageToonFilter;
import com.ben.android.library.filter.GPUImageVibranceFilter;
import com.ben.android.library.filter.GPUImageVignetteFilter;
import com.ben.android.library.filter.GPUImageWeakPixelInclusionFilter;
import com.ben.android.library.filter.GPUImageWhiteBalanceFilter;
import com.ben.android.library.filter.GaussianBlurFilter;
import com.ben.android.library.filter.NativeFilter;
import com.ben.android.library.filter.PixelationFilter;
import com.ben.android.library.filter.ZoomBlurFilter;
import com.ben.android.nativegpuimage.R;
import com.chad.library.adapter.base.BaseQuickAdapter;
import com.chad.library.adapter.base.BaseViewHolder;

import java.util.ArrayList;

public class ImageAdapter extends BaseQuickAdapter<NativeFilter, BaseViewHolder> {
    private int width;
    private int height;

    public ImageAdapter(final Context context) {
        super(R.layout.item_image_layout, new ArrayList<NativeFilter>() {
            {
                add(new GPUImageHazeFilter());
                add(new GPUImageHighlightShadowFilter(0.5f,0.5f));
                add(new GPUImageSharpenFilter(-4.0f));
                add(new GPUImageMonochromeFilter(0.5f));
                add(new GPUImageHueFilter(50f));
                add(new GPUImageRGBDilationFilter(3));
                add(new GPUImageRGBFilter(1.0f,0.5f,0.5f));
                add(new GPUImageLevelsFilter(0.0f,0.3f,1.0f));
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
                add(new GPUImageAddBlendFilter(BitmapFactory.decodeResource(context.getResources(), R.drawable.lookup_amatorka)));
                add(new GPUImageAddBlendFilter(BitmapFactory.decodeResource(context.getResources(), R.drawable.lookup_amatorka)));
                add(new GPUImageToonFilter(0.5f, 20.0f));
                add(new GPUImageGammaFilter(2.0f));
                add(new GPUImageFalseColorFilter());
                add(new GPUImageExposureFilter());
                add(new GPUImageExclusionBlendFilter());
                add(new GPUImage3x3ConvolutionFilter(new float[]{0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f}));
                add(new GPUImageEmbossFilter());
                add(new GPUImageDivideBlendFilter(BitmapFactory.decodeResource(context.getResources(), R.drawable.lookup_amatorka)));
                add(new GPUImageAlphaBlendFilter(BitmapFactory.decodeResource(context.getResources(), R.drawable.lookup_amatorka), 0.5f));
                add(new GPUImageDissolveBlendFilter(BitmapFactory.decodeResource(context.getResources(), R.drawable.lookup_amatorka), 1.0f));
            }
        });
    }

    @Override
    protected void convert(@NonNull BaseViewHolder helper, NativeFilter item) {
        NGPNativeBridge.setFilter(item);
        Bitmap resultBitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
        NGPNativeBridge.capture(resultBitmap);
        helper.setImageBitmap(R.id.mImageView, resultBitmap);
    }

    public int getWidth() {
        return width;
    }

    public void setWidth(int width) {
        this.width = width;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }
}
