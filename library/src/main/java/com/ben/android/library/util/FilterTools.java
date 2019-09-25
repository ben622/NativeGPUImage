package com.ben.android.library.util;

import com.ben.android.library.filter.NativeFilter;

public class FilterTools {
    public static NativeFilter createJavaFilterObject(FilterType filterType) {
        NativeFilter filter = null;
        switch (filterType) {
            case CONTRAST:
                filter = new NativeFilter();
                break;
            case GRAYSCALE:
                filter = new NativeFilter();
                break;
            case SHARPEN:
                filter = new NativeFilter();
                break;
            case SEPIA:
                filter = new NativeFilter();
                break;
            case SOBEL_EDGE_DETECTION:
                filter = new NativeFilter();
                break;
            case THRESHOLD_EDGE_DETECTION:
                filter = new NativeFilter();
                break;
            case THREE_X_THREE_CONVOLUTION:
                filter = new NativeFilter();
                break;
            case FILTER_GROUP:
                filter = new NativeFilter();
                break;
            case EMBOSS:
                filter = new NativeFilter();
                break;
            case POSTERIZE:
                filter = new NativeFilter();
                break;
            case GAMMA:
                filter = new NativeFilter();
                break;
            case BRIGHTNESS:
                filter = new NativeFilter();
                break;
            case INVERT:
                filter = new NativeFilter();
                break;
            case HUE:
                filter = new NativeFilter();
                break;
            case PIXELATION:
                //filter = new GPUImagePixelationFilter();
                break;
            case SATURATION:
                filter = new NativeFilter();
                break;
            case EXPOSURE:
                filter = new NativeFilter();
                break;
            case HIGHLIGHT_SHADOW:
                filter = new NativeFilter();
                break;
            case MONOCHROME:
                filter = new NativeFilter();
                break;
            case OPACITY:
                filter = new NativeFilter();
                break;
            case RGB:
                filter = new NativeFilter();
                break;
            case WHITE_BALANCE:
                filter = new NativeFilter();
                break;
            case VIGNETTE:
                filter = new NativeFilter();
                break;
            case TONE_CURVE:
                filter = new NativeFilter();
                break;
            case LUMINANCE:
                filter = new NativeFilter();
                break;
            case LUMINANCE_THRESHSOLD:
                filter = new NativeFilter();
                break;
            case BLEND_COLOR_BURN:
                filter = new NativeFilter();
                break;
            case BLEND_COLOR_DODGE:
                filter = new NativeFilter();
                break;
            case BLEND_DARKEN:
                filter = new NativeFilter();
                break;
            case BLEND_DIFFERENCE:
                filter = new NativeFilter();
                break;
            case BLEND_DISSOLVE:
                filter = new NativeFilter();
                break;
            case BLEND_EXCLUSION:
                filter = new NativeFilter();
                break;
            case BLEND_SOURCE_OVER:
                filter = new NativeFilter();
                break;
            case BLEND_HARD_LIGHT:
                filter = new NativeFilter();
                break;
            case BLEND_LIGHTEN:
                filter = new NativeFilter();
                break;
            case BLEND_ADD:
                filter = new NativeFilter();
                break;
            case BLEND_DIVIDE:
                filter = new NativeFilter();
                break;
            case BLEND_MULTIPLY:
                filter = new NativeFilter();
                break;
            case BLEND_OVERLAY:
                filter = new NativeFilter();
                break;
            case BLEND_SCREEN:
                filter = new NativeFilter();
                break;
            case BLEND_ALPHA:
                filter = new NativeFilter();
                break;
            case BLEND_COLOR:
                filter = new NativeFilter();
                break;
            case BLEND_HUE:
                filter = new NativeFilter();
                break;
            case BLEND_SATURATION:
                filter = new NativeFilter();
                break;
            case BLEND_LUMINOSITY:
                filter = new NativeFilter();
                break;
            case BLEND_LINEAR_BURN:
                filter = new NativeFilter();
                break;
            case BLEND_SOFT_LIGHT:
                filter = new NativeFilter();
                break;
            case BLEND_SUBTRACT:
                filter = new NativeFilter();
                break;
            case BLEND_CHROMA_KEY:
                filter = new NativeFilter();
                break;
            case BLEND_NORMAL:
                filter = new NativeFilter();
                break;
            case LOOKUP_AMATORKA:
                filter = new NativeFilter();
                break;
            case GAUSSIAN_BLUR:
                //高斯滤波
                //filter = new GPUImageGaussianBlurFilter();
                break;
            case CROSSHATCH:
                filter = new NativeFilter();
                break;
            case BOX_BLUR:
                filter = new NativeFilter();
                break;
            case CGA_COLORSPACE:
                filter = new NativeFilter();
                break;
            case DILATION:
                //filter = new GPUImageDilationFilter();
                break;
            case KUWAHARA:
                filter = new NativeFilter();
                break;
            case RGB_DILATION:
                filter = new NativeFilter();
                break;
            case SKETCH:
                filter = new NativeFilter();
                break;
            case TOON:
                filter = new NativeFilter();
                break;
            case SMOOTH_TOON:
                filter = new NativeFilter();
                break;
            case BULGE_DISTORTION:
                filter = new NativeFilter();
                break;
            case GLASS_SPHERE:
                filter = new NativeFilter();
                break;
            case HAZE:
                filter = new NativeFilter();
                break;
            case LAPLACIAN:
                filter = new NativeFilter();
                break;
            case NON_MAXIMUM_SUPPRESSION:
                filter = new NativeFilter();
                break;
            case SPHERE_REFRACTION:
                filter = new NativeFilter();
                break;
            case SWIRL:
                filter = new NativeFilter();
                break;
            case WEAK_PIXEL_INCLUSION:
                filter = new NativeFilter();
                break;
            case FALSE_COLOR:
                filter = new NativeFilter();
                break;
            case COLOR_BALANCE:
                filter = new NativeFilter();
                break;
            case LEVELS_FILTER_MIN:
                filter = new NativeFilter();
                break;
            case BILATERAL_BLUR:
                filter = new NativeFilter();
                break;
            case ZOOM_BLUR:
                //filter = new GPUImageZoomBlurFilter();
                break;
            case HALFTONE:
                filter = new NativeFilter();
                break;
            case TRANSFORM2D:
                filter = new NativeFilter();
                break;
            case SOLARIZE:
                filter = new NativeFilter();
                break;
            case VIBRANCE:
                filter = new NativeFilter();
                break;
            default :

                filter = new NativeFilter();
                break;
        }
        return filter;
    }
}
