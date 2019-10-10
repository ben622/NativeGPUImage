package com.ben.android.nativegpuimage;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;

import com.ben.android.library.NGP;
import com.ben.android.library.NGPNativeBridge;
import com.ben.android.library.filter.GPUImageBrightnessFilter;
import com.ben.android.library.filter.GPUImageContrastFilter;
import com.ben.android.library.filter.GPUImageCrosshatchFilter;
import com.ben.android.library.filter.GPUImageHazeFilter;
import com.ben.android.library.filter.GPUImageSaturationFilter;
import com.ben.android.library.filter.GPUImageSobelEdgeDetectionFilter;
import com.ben.android.library.filter.GPUImageSolarizeFilter;
import com.ben.android.library.filter.GPUImageThresholdEdgeDetectionFilter;

public class FBOActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fbo);
        NGPNativeBridge.init();

    }

    public void OnClick(View view) {

        final ImageView imageView = new ImageView(this);
       /* new AlertDialog.Builder(this)
                .setView(imageView)
                .create().show();*/

       new Thread(new Runnable() {
           @Override
           public void run() {
               NGP.with(FBOActivity.this)
                       .applyBitmapByUrls(
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg",
                               "https://avatars0.githubusercontent.com/u/20227667?s=460&v=4",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702810156&di=8685cb31897512fc97f4fd59bf1c9ad8&imgtype=0&src=http%3A%2F%2Fb-ssl.duitang.com%2Fuploads%2Fitem%2F201510%2F23%2F20151023130259_VNya5.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702842483&di=2668786ec7ef0fabc7d23693f47ed3ce&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20190603%2F347056f5d88b4a16ae66d69d831c6de7.jpeg",
                               "https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1570702863594&di=8fcf0248c9b800f717ff0833d5f30341&imgtype=0&src=http%3A%2F%2Fimg.mp.itc.cn%2Fupload%2F20170103%2Fc2e55cfd15d0420488831213b6035222_th.jpeg",
                               "https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1303676042,3415822080&fm=26&gp=0.jpg"

                       )
                       .applyFilter(new GPUImageSaturationFilter(2.0f))
                       //.applyWidth(1000)   //指定宽度渲染，不指定宽度则按原图宽度渲染
                       //.applyHeight(1000)  //指定高度渲染，不指定高度则按原图高度渲染
                       .isAsync(false)     //当前线程同步渲染
                       .into(imageView);
           }
       }).start();


    }
}
