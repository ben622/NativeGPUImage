//
// Created by TY on 2018/5/21.
//

#ifndef ANDROIDOPENGLDEMO_ASSETSREADER_H
#define ANDROIDOPENGLDEMO_ASSETSREADER_H

#include "jni.h"
#include "android/asset_manager_jni.h"
#include "CommonTools.h"
#define LOG_TAG "readSource"

void mallocContent(AAsset *pAsset, char *&content);

void readSource(JNIEnv* env, const char* vertexFilePath,
                const char* fragFilePath,
                jobject assetManager,
                char*& vertexContent,
                char*& fragContent){

    LOGI("ReadAssets");
    AAssetManager* mgr=AAssetManager_fromJava(env,assetManager);
    if(mgr==NULL)
    {
        LOGI(" %s","AAssetManager==NULL");
        return ;
    }
    AAsset* assetVertex=AAssetManager_open(mgr,vertexFilePath,AASSET_MODE_BUFFER);
    if(assetVertex==NULL)
    {
        LOGI(" %s","asset==NULL");
        return ;
    }
    mallocContent(assetVertex,vertexContent);
    AAsset* assetFrag=AAssetManager_open(mgr,fragFilePath,AASSET_MODE_BUFFER);
    if(assetFrag==NULL)
    {
        LOGI(" %s","asset==NULL");
        return ;
    }
    mallocContent(assetFrag,fragContent);
}

void mallocContent(AAsset *pAsset, char* &content) {
    off_t  bufferSize=AAsset_getLength(pAsset);
    LOGI("file size: %d\n",bufferSize);
    content=new char[bufferSize+1];
    content[bufferSize]=0;
    int numBytesRead=AAsset_read(pAsset,content,bufferSize);
    AAsset_close(pAsset);
}
#endif //ANDROIDOPENGLDEMO_ASSETSREADER_H
