package com.ben.android.nativegpuimage

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.graphics.PointF
import android.os.Build
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v7.app.AlertDialog
import android.support.v7.widget.LinearLayoutManager
import android.view.View
import android.widget.ImageView
import android.widget.SeekBar
import com.ben.android.library.NGP
import com.ben.android.library.NGPNativeBridge
import com.ben.android.library.filter.*
import com.ben.android.library.util.Rotation
import com.ben.android.nativegpuimage.adapter.ImageAdapter
import com.chad.library.adapter.base.BaseQuickAdapter
import jp.co.cyberagent.android.gpuimage.sample.utils.Camera1Loader
import jp.co.cyberagent.android.gpuimage.sample.utils.Camera2Loader
import jp.co.cyberagent.android.gpuimage.sample.utils.CameraLoader
import kotlinx.android.synthetic.main.activity_camera.*
import kotlinx.android.synthetic.main.activity_camera.mRecyclerView
import kotlinx.android.synthetic.main.activity_camera.mSurfaceView
import kotlinx.android.synthetic.main.activity_camera.seekBar
import kotlinx.android.synthetic.main.activity_image.*

class CameraActivity : AppCompatActivity() {
    private var filterAdjuster: GPUImageFilterTools.FilterAdjuster? = null
    private val cameraLoader: CameraLoader by lazy {
        if (Build.VERSION.SDK_INT < 21) {
            Camera1Loader(this)
        } else {
            Camera2Loader(this)
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setTitle("NativeGPUImage Camera Demo")
        setContentView(R.layout.activity_camera)
        seekBar.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                filterAdjuster?.adjust(progress)
                var filter = filterAdjuster?.getFilter()
                if (filter != null) {
                    NGPNativeBridge.nativeApplyFilter(filter)
                    //不用手动调用Request了，因为当调用NGPNativeBridge.nativeApplyYUV420时已经在Native中调用了Request。
                    //NGPNativeBridge.nativeRequestRender()
                }
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {}
            override fun onStopTrackingTouch(seekBar: SeekBar?) {}
        })

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


        var adapter = ImageAdapter(this)
        mRecyclerView.layoutManager = LinearLayoutManager(this, LinearLayoutManager.HORIZONTAL, false)
        mRecyclerView.adapter = adapter


        adapter.setOnItemClickListener(object : BaseQuickAdapter.OnItemClickListener {
            override fun onItemClick(_adapter: BaseQuickAdapter<*, *>?, view: View?, position: Int) {
                filterAdjuster = GPUImageFilterTools.FilterAdjuster(filters.get(position))
                if (filterAdjuster!!.canAdjust()) {
                    seekBar.visibility = View.VISIBLE
                    filterAdjuster!!.adjust(seekBar.progress)
                } else {
                    seekBar.visibility = View.GONE
                }
                var filter = filterAdjuster!!.getFilter()
                if (filter != null) {
                    NGPNativeBridge.nativeApplyFilter(filter)
                } else {
                    NGPNativeBridge.nativeApplyFilter(filters.get(position))
                }
                NGPNativeBridge.nativeRequestRender()

            }

        })


        Thread({
            var result = NGP.with(this)
                    .applyBitmaps(R.drawable.photo4)
                    .applyMultipleFilter(filters)
                    .build()
                    .get()
            runOnUiThread {
                adapter.setNewData(result)
                mProgress.visibility = View.GONE

                cameraLoader.setOnPreviewFrameListener { data, width, height ->
                    NGPNativeBridge.nativeApplyYUV420(data, width, height)
                }

                mSurfaceView.initialize({
                    NGPNativeBridge.nativeApplyFilter(GPUImageGrayscaleFilter())
                    NGPNativeBridge.nativeApplyRotation(Rotation.getValue(getRotation(cameraLoader.getCameraOrientation())), false, false)
                })
                mCapture.setOnClickListener {
                    val imageView = ImageView(this)
                    var capture = Bitmap.createBitmap(mSurfaceView.measuredWidth, mSurfaceView.measuredHeight, Bitmap.Config.ARGB_8888)
                    NGPNativeBridge.nativeCapture(capture)
                    imageView.setImageBitmap(capture)
                    AlertDialog.Builder (this)
                            .setView(imageView)
                            .setOnDismissListener {
                                capture.recycle()
                                capture = null
                            }
                            .create().show();
                }
                mCapture.visibility = View.VISIBLE
            }
        }).start()

    }

    override fun onResume() {
        super.onResume()
        mSurfaceView.doOnLayout {
            cameraLoader.onResume(it.width, it.height)
        }
    }

    override fun onPause() {
        cameraLoader.onPause()
        super.onPause()
    }

    fun getRotation(orientation: Int): Rotation {
        return when (orientation) {
            90 -> Rotation.ROTATION_90
            180 -> Rotation.ROTATION_180
            270 -> Rotation.ROTATION_270
            else -> Rotation.NORMAL
        }
    }


}
