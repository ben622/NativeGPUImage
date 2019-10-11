package com.ben.android.nativegpuimage

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.graphics.Canvas
import android.graphics.PointF
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v7.widget.LinearLayoutManager
import android.view.View
import android.view.Window
import android.view.WindowManager
import com.ben.android.library.NGP
import com.ben.android.library.NGPFilterListener
import com.ben.android.library.NGPNativeBridge
import com.ben.android.library.filter.*
import com.ben.android.library.render.Render
import com.ben.android.nativegpuimage.adapter.ImageAdapter
import com.bumptech.glide.Glide
import com.chad.library.adapter.base.BaseQuickAdapter
import kotlinx.android.synthetic.main.activity_image.*
import kotlinx.android.synthetic.main.activity_main.*
import java.io.File
import java.util.*


class ImageActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        supportRequestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_image)

        var adapter = ImageAdapter(this)
        mRecyclerView.layoutManager = LinearLayoutManager(this, LinearLayoutManager.HORIZONTAL, false)
        mRecyclerView.adapter = adapter

        adapter.setOnItemClickListener(object : BaseQuickAdapter.OnItemClickListener {
            override fun onItemClick(_adapter: BaseQuickAdapter<*, *>?, view: View?, position: Int) {
                Glide.with(applicationContext).load(File(adapter.data.get(position).path)).into(mImageView)
            }

        })

        Thread({
            var result = NGP.with(this)
                    .applyBitmaps(R.drawable.photo1)
                    .applyMultipleFilter(
                            GPUImageSketchFilter(),
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
                    .build()
                    .get()

            runOnUiThread {
                adapter.setNewData(result)
                Glide.with(applicationContext).load(File(adapter.data.get(0).path)).into(mImageView)
            }


        }).start()


    }
}
