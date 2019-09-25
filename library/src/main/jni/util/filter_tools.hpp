/*
//
// Created by ben622 on 2019/9/24.
//

#ifndef NATIVEGPUIMAGE_FILTER_TOOLS_HPP
#define NATIVEGPUIMAGE_FILTER_TOOLS_HPP

#include "../filter/gpu_image_gaussian_blur_filter.hpp"
#include "../filter/gpu_image_pixelation_filter.hpp"
#include "../filter/gpu_image_dilation_filter.hpp"
#include "../filter/gpu_image_zoom_blur_filter.hpp"
using namespace ben::ngp;
namespace ben {
    namespace util {


        static GPUImageFilter *createGPUImageFilter(int filterType) {
            createGPUImageFilter(static_cast<FilterType>(filterType));
        }

        static GPUImageFilter *createGPUImageFilter(FilterType filterType) {
            GPUImageFilter *filter;
            switch (filterType) {
                case CONTRAST:
                    filter = new GPUImageFilter();
                    break;
                case GRAYSCALE:
                    filter = new GPUImageFilter();
                    break;
                case SHARPEN:
                    filter = new GPUImageFilter();
                    break;
                case SEPIA:
                    filter = new GPUImageFilter();
                    break;
                case SOBEL_EDGE_DETECTION:
                    filter = new GPUImageFilter();
                    break;
                case THRESHOLD_EDGE_DETECTION:
                    filter = new GPUImageFilter();
                    break;
                case THREE_X_THREE_CONVOLUTION:
                    filter = new GPUImageFilter();
                    break;
                case FILTER_GROUP:
                    filter = new GPUImageFilter();
                    break;
                case EMBOSS:
                    filter = new GPUImageFilter();
                    break;
                case POSTERIZE:
                    filter = new GPUImageFilter();
                    break;
                case GAMMA:
                    filter = new GPUImageFilter();
                    break;
                case BRIGHTNESS:
                    filter = new GPUImageFilter();
                    break;
                case INVERT:
                    filter = new GPUImageFilter();
                    break;
                case HUE:
                    filter = new GPUImageFilter();
                    break;
                case PIXELATION:
                    filter = new GPUImagePixelationFilter();
                    break;
                case SATURATION:
                    filter = new GPUImageFilter();
                    break;
                case EXPOSURE:
                    filter = new GPUImageFilter();
                    break;
                case HIGHLIGHT_SHADOW:
                    filter = new GPUImageFilter();
                    break;
                case MONOCHROME:
                    filter = new GPUImageFilter();
                    break;
                case OPACITY:
                    filter = new GPUImageFilter();
                    break;
                case RGB:
                    filter = new GPUImageFilter();
                    break;
                case WHITE_BALANCE:
                    filter = new GPUImageFilter();
                    break;
                case VIGNETTE:
                    filter = new GPUImageFilter();
                    break;
                case TONE_CURVE:
                    filter = new GPUImageFilter();
                    break;
                case LUMINANCE:
                    filter = new GPUImageFilter();
                    break;
                case LUMINANCE_THRESHSOLD:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_COLOR_BURN:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_COLOR_DODGE:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_DARKEN:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_DIFFERENCE:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_DISSOLVE:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_EXCLUSION:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_SOURCE_OVER:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_HARD_LIGHT:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_LIGHTEN:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_ADD:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_DIVIDE:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_MULTIPLY:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_OVERLAY:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_SCREEN:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_ALPHA:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_COLOR:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_HUE:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_SATURATION:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_LUMINOSITY:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_LINEAR_BURN:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_SOFT_LIGHT:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_SUBTRACT:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_CHROMA_KEY:
                    filter = new GPUImageFilter();
                    break;
                case BLEND_NORMAL:
                    filter = new GPUImageFilter();
                    break;
                case LOOKUP_AMATORKA:
                    filter = new GPUImageFilter();
                    break;
                case GAUSSIAN_BLUR:
                    //高斯滤波
                    filter = new GPUImageGaussianBlurFilter();
                    break;
                case CROSSHATCH:
                    filter = new GPUImageFilter();
                    break;
                case BOX_BLUR:
                    filter = new GPUImageFilter();
                    break;
                case CGA_COLORSPACE:
                    filter = new GPUImageFilter();
                    break;
                case DILATION:
                    filter = new GPUImageDilationFilter();
                    break;
                case KUWAHARA:
                    filter = new GPUImageFilter();
                    break;
                case RGB_DILATION:
                    filter = new GPUImageFilter();
                    break;
                case SKETCH:
                    filter = new GPUImageFilter();
                    break;
                case TOON:
                    filter = new GPUImageFilter();
                    break;
                case SMOOTH_TOON:
                    filter = new GPUImageFilter();
                    break;
                case BULGE_DISTORTION:
                    filter = new GPUImageFilter();
                    break;
                case GLASS_SPHERE:
                    filter = new GPUImageFilter();
                    break;
                case HAZE:
                    filter = new GPUImageFilter();
                    break;
                case LAPLACIAN:
                    filter = new GPUImageFilter();
                    break;
                case NON_MAXIMUM_SUPPRESSION:
                    filter = new GPUImageFilter();
                    break;
                case SPHERE_REFRACTION:
                    filter = new GPUImageFilter();
                    break;
                case SWIRL:
                    filter = new GPUImageFilter();
                    break;
                case WEAK_PIXEL_INCLUSION:
                    filter = new GPUImageFilter();
                    break;
                case FALSE_COLOR:
                    filter = new GPUImageFilter();
                    break;
                case COLOR_BALANCE:
                    filter = new GPUImageFilter();
                    break;
                case LEVELS_FILTER_MIN:
                    filter = new GPUImageFilter();
                    break;
                case BILATERAL_BLUR:
                    filter = new GPUImageFilter();
                    break;
                case ZOOM_BLUR:
                    filter = new GPUImageZoomBlurFilter();
                    break;
                case HALFTONE:
                    filter = new GPUImageFilter();
                    break;
                case TRANSFORM2D:
                    filter = new GPUImageFilter();
                    break;
                case SOLARIZE:
                    filter = new GPUImageFilter();
                    break;
                case VIBRANCE:
                    filter = new GPUImageFilter();
                    break;
                default :

                    filter = new GPUImageFilter();
                    break;
            }
            return filter;
        }
    }
}
#endif //NATIVEGPUIMAGE_FILTER_TOOLS_HPP
*/
