package com.ben.android.nativegpuimage

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.graphics.Canvas
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v7.widget.LinearLayoutManager
import android.view.View
import android.view.Window
import android.view.WindowManager
import com.ben.android.library.NGPNativeBridge
import com.ben.android.nativegpuimage.adapter.ImageAdapter
import com.chad.library.adapter.base.BaseQuickAdapter
import kotlinx.android.synthetic.main.activity_image.*


class ImageActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        supportRequestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        NGPNativeBridge.init()
        setContentView(R.layout.activity_image)

        mGPUImageRender.setOnEGPEnvironmentListener {
            val bitmap = BitmapFactory.decodeResource(resources, com.ben.android.library.R.mipmap.dog)
            val resizedBitmap = Bitmap.createBitmap(bitmap.width, bitmap.height,
                    Bitmap.Config.ARGB_8888)
            val can = Canvas(resizedBitmap)
            can.drawARGB(0x00, 0x00, 0x00, 0x00)
            can.drawBitmap(bitmap, 0f, 0f, null)
            NGPNativeBridge.nativeApplyBitmap(resizedBitmap)
            NGPNativeBridge.nativeRequestRender()

            var adapter = ImageAdapter(this)
            adapter.width = mGPUImageRender.measuredWidth
            adapter.height = mGPUImageRender.measuredHeight
            mRecyclerView.layoutManager = LinearLayoutManager(this, LinearLayoutManager.HORIZONTAL, false)
            mRecyclerView.adapter = adapter
            adapter.setOnItemClickListener(object : BaseQuickAdapter.OnItemClickListener {
                override fun onItemClick(_adapter: BaseQuickAdapter<*, *>?, view: View?, position: Int) {
                    NGPNativeBridge.nativeApplyFilter(adapter.data.get(position))
                    NGPNativeBridge.nativeRequestRender()
                }

            })
        }


    }
}
