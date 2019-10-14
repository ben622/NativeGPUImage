package com.ben.android.nativegpuimage

import android.graphics.BitmapFactory
import android.graphics.PointF
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import com.ben.android.library.NGP
import com.ben.android.library.NGPFilterListener
import com.ben.android.library.NGPListener
import com.ben.android.library.Result
import com.ben.android.library.filter.*
import com.ben.android.library.render.Render
import kotlinx.android.synthetic.main.activity_show_bitmap.*

class ShowBitmapActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_show_bitmap)

        var filters = arrayListOf(
                //GPUImageSketchFilter(),
                GPUImageThresholdEdgeDetectionFilter(),
                GPUImageCrosshatchFilter(),
                GPUImageHalftoneFilter(),
                GPUImageLuminanceThresholdFilter(),
                GPUImageLuminanceFilter(),
                GPUImageSolarizeFilter(0.01f),
                GPUImageHazeFilter(),
                GPUImageHighlightShadowFilter(0.5f, 0.5f),
                GPUImageSharpenFilter(-4.0f),
                GPUImageMonochromeFilter(0.5f),
                GPUImageHueFilter(50f),
                GPUImageRGBDilationFilter(3),
                GPUImageRGBFilter(1.0f, 0.5f, 0.5f),
                GPUImageLevelsFilter(0.0f, 0.3f, 1.0f),
                GPUImageBrightnessFilter(0.5f),
                GPUImageContrastFilter(2.0f),
                GPUImageSaturationFilter(2.0f),
                PixelationFilter(30f),
                ZoomBlurFilter(PointF(0.7f, 0.7f), 1.0f),
                DilationFilter(1),
                GaussianBlurFilter(10f),
                GPUImageWhiteBalanceFilter(1000f, 1.0f),
                GPUImageWeakPixelInclusionFilter(),
                GPUImageVignetteFilter(PointF(0.5f, 0.5f), floatArrayOf(0.0f, 0.0f, 0.0f), 0.2f, 0.75f),
                GPUImageSobelEdgeDetectionFilter(1.7f),
                GPUImageGrayscaleFilter(),
                GPUImageVibranceFilter(1.5f),
                GPUImageAddBlendFilter(BitmapFactory.decodeResource(getResources(), R.drawable.lookup_amatorka)),
                GPUImageAddBlendFilter(BitmapFactory.decodeResource(getResources(), R.drawable.lookup_amatorka)),
                GPUImageToonFilter(0.5f, 20.0f),
                GPUImageGammaFilter(2.0f),
                GPUImageFalseColorFilter(),
                GPUImageExposureFilter(),
                GPUImageExclusionBlendFilter(),
                GPUImage3x3ConvolutionFilter(floatArrayOf(0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f)),
                GPUImageEmbossFilter(),
                GPUImageDivideBlendFilter(BitmapFactory.decodeResource(getResources(), R.drawable.lookup_amatorka)),
                GPUImageAlphaBlendFilter(BitmapFactory.decodeResource(getResources(), R.drawable.lookup_amatorka), 0.5f),
                GPUImageDissolveBlendFilter(BitmapFactory.decodeResource(getResources(), R.drawable.lookup_amatorka), 1.0f)
        )

        NGP.with(this)
                .applyBitmapByUrls("http://www.zhangchuany.com/photo5.jpg")
                .applyFilter(GPUImageGrayscaleFilter())
                .applyNGPFilter(object :NGPFilterListener{
                    override fun apply(render: Render.UpgradRender, position: Int): Render.UpgradRender {
                        //随机选择一个滤镜
                        render.filter = filters.random()
                        return render
                    }
                })
                .autoFile(false)
                .build()
                .into(mImageView)
    }
}
