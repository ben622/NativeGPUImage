//
// Created by ben622 on 2019/9/20.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_PIXELATION_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_PIXELATION_FILTER_HPP

#include "gpu_image_filter.hpp"
#define GET_STR(x) #x
static char *PIXELATION_FRAGMENT_SHADER = GET_STR(
        precision highp float;

        varying vec2 textureCoordinate;

        uniform float imageWidthFactor;
        uniform float imageHeightFactor;
        uniform sampler2D inputImageTexture;
        uniform float pixel;

        void main()
        {
            vec2 uv  = textureCoordinate.xy;
            float dx = pixel * imageWidthFactor;
            float dy = pixel * imageHeightFactor;
            vec2 coord = vec2(dx * floor(uv.x / dx), dy * floor(uv.y / dy));
            vec3 tc = texture2D(inputImageTexture, coord).xyz;
            gl_FragColor = vec4(tc, 1.0);
        }
);

namespace ben {
    namespace ngp {
        class GPUImagePixelationFilter : public ben::ngp::GPUImageFilter {
        private:
            int imageWidthFactorLocation;
            int imageHeightFactorLocation;
            float pixel;
            int pixelLocation;
        public:
            GPUImagePixelationFilter();

        public:

            void onOutputSizeChanged(int width, int height);

            void onInit();

            void onInitialized();

            void setPixel(float pixel);

            int getImageWidthFactorLocation() const;

            void setImageWidthFactorLocation(int imageWidthFactorLocation);

            int getImageHeightFactorLocation() const;

            void setImageHeightFactorLocation(int imageHeightFactorLocation);

            float getPixel() const;

            int getPixelLocation() const;

            void setPixelLocation(int pixelLocation);
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_PIXELATION_FILTER_HPP
