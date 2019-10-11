package com.ben.android.nativegpuimage.adapter;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.PointF;
import android.support.annotation.NonNull;
import android.widget.ImageView;

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
import com.ben.android.nativegpuimage.R;
import com.bumptech.glide.Glide;
import com.chad.library.adapter.base.BaseQuickAdapter;
import com.chad.library.adapter.base.BaseViewHolder;

import java.io.File;
import java.util.ArrayList;

public class ImageAdapter extends BaseQuickAdapter<Result, BaseViewHolder> {

    public ImageAdapter(final Context context) {
        super(R.layout.item_image_layout);
    }

    @Override
    protected void convert(@NonNull BaseViewHolder helper, Result item) {
        Glide.with(mContext).load(new File(item.getPath())).into((ImageView) helper.getView(R.id.mImageView));
    }
}
