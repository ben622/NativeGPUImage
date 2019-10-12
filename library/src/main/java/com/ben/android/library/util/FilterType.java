package com.ben.android.library.util;

import com.ben.android.library.filter.NativeFilter;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/12
 */
public enum FilterType {
    CONTRAST,
    GRAYSCALE,
    SHARPEN,
    SEPIA,
    SOBEL_EDGE_DETECTION,
    THRESHOLD_EDGE_DETECTION,
    THREE_X_THREE_CONVOLUTION,
    FILTER_GROUP,
    EMBOSS,
    POSTERIZE,
    GAMMA,
    BRIGHTNESS,
    INVERT,
    HUE,
    PIXELATION,
    SATURATION,
    EXPOSURE,
    HIGHLIGHT_SHADOW,
    MONOCHROME,
    OPACITY,
    RGB,
    WHITE_BALANCE,
    VIGNETTE,
    TONE_CURVE,
    LUMINANCE,
    LUMINANCE_THRESHSOLD,
    BLEND_COLOR_BURN,
    BLEND_COLOR_DODGE,
    BLEND_DARKEN,
    BLEND_DIFFERENCE,
    BLEND_DISSOLVE,
    BLEND_EXCLUSION,
    BLEND_SOURCE_OVER,
    BLEND_HARD_LIGHT,
    BLEND_LIGHTEN,
    BLEND_ADD,
    BLEND_DIVIDE,
    BLEND_MULTIPLY,
    BLEND_OVERLAY,
    BLEND_SCREEN,
    BLEND_ALPHA,
    BLEND_COLOR,
    BLEND_HUE,
    BLEND_SATURATION,
    BLEND_LUMINOSITY,
    BLEND_LINEAR_BURN,
    BLEND_SOFT_LIGHT,
    BLEND_SUBTRACT,
    BLEND_CHROMA_KEY,
    BLEND_NORMAL,
    LOOKUP_AMATORKA,
    GAUSSIAN_BLUR,
    CROSSHATCH,
    BOX_BLUR,
    CGA_COLORSPACE,
    DILATION,
    KUWAHARA,
    RGB_DILATION,
    SKETCH,
    TOON,
    SMOOTH_TOON,
    BULGE_DISTORTION,
    GLASS_SPHERE,
    HAZE,
    LAPLACIAN,
    NON_MAXIMUM_SUPPRESSION,
    SPHERE_REFRACTION,
    SWIRL,
    WEAK_PIXEL_INCLUSION,
    FALSE_COLOR,
    COLOR_BALANCE,
    LEVELS_FILTER_MIN,
    BILATERAL_BLUR,
    ZOOM_BLUR,
    HALFTONE,
    TRANSFORM2D,
    SOLARIZE,
    VIBRANCE,
    SOBEL_THRESHOLD;

    public static FilterType valueOf(int type) {
        for (FilterType value : values()) {
            if (type == value.ordinal()) {
                return value;
            }
        }
        return FilterType.VIBRANCE;
    }
    public static String getFilterName(NativeFilter filter) {
        if (filter==null) return null;
        switch (FilterType.valueOf(filter.getFilterType())) {
            case CONTRAST: {
                return "Contrast";
            }
            case GRAYSCALE: {
                return "Grayscale";
            }
            case SHARPEN: {
                return "Sharpness";
            }
            case SEPIA: {
                return "Sepia";
            }
            case SOBEL_EDGE_DETECTION: {
                return "Sobel Edge Detection";
            }
            case THRESHOLD_EDGE_DETECTION: {
                return "Threshold Edge Detection";
            }
            case SOBEL_THRESHOLD: {
                return "SOBEL_THRESHOLD";
            }
            case THREE_X_THREE_CONVOLUTION: {
                return "3x3 Convolution";
            }
            case FILTER_GROUP: {
                return "Filter Group";
            }
            case EMBOSS: {
                return "Emboss";
            }
            case POSTERIZE: {
                return "Posterize";
            }
            case GAMMA: {
                return "Gamma";
            }
            case BRIGHTNESS: {
                return "Brightness";
            }
            case INVERT: {
                return "Invert";
            }
            case HUE: {
                return "Hue";
            }
            case PIXELATION: {
                return "Pixelation";
            }
            case SATURATION: {
                return "Saturation";
            }
            case EXPOSURE: {
                return "Exposure";
            }
            case HIGHLIGHT_SHADOW: {
                return "Highlight Shadow";
            }
            case MONOCHROME: {
                return "Monochrome";
            }
            case OPACITY: {
                return "Opacity";
            }
            case RGB: {
                return "RGB";
            }
            case WHITE_BALANCE: {
                return "White Balance";
            }
            case VIGNETTE: {
                return "Vignette";
            }
            case TONE_CURVE: {
                return "ToneCurve";
            }
            case LUMINANCE: {
                return "Luminance";
            }
            case LUMINANCE_THRESHSOLD: {
                return "Luminance Threshold";
            }
            case BLEND_COLOR_BURN: {
                return "Blend (Color Burn)";
            }
            case BLEND_COLOR_DODGE: {
                return "Blend (Color Dodge)";
            }
            case BLEND_DARKEN: {
                return "Blend (Darken)";
            }
            case BLEND_DIFFERENCE: {
                return "Blend (Difference)";
            }
            case BLEND_DISSOLVE: {
                return "Blend (Dissolve)";
            }
            case BLEND_EXCLUSION: {
                return "Blend (Exclusion)";
            }
            case BLEND_SOURCE_OVER: {
                return "Blend (Source Over)";
            }
            case BLEND_HARD_LIGHT: {
                return "Blend (Hard Light)";
            }
            case BLEND_LIGHTEN: {
                return "Blend (Lighten)";
            }
            case BLEND_ADD: {
                return "Blend (Add)";
            }
            case BLEND_DIVIDE: {
                return "Blend (Divide)";
            }
            case BLEND_MULTIPLY: {
                return "Blend (Multiply)";
            }
            case BLEND_OVERLAY: {
                return "Blend (Overlay)";
            }
            case BLEND_SCREEN: {
                return "Blend (Screen)";
            }
            case BLEND_ALPHA: {
                return "Blend (Alpha)";
            }
            case BLEND_COLOR: {
                return "Blend (Color)";
            }
            case BLEND_HUE: {
                return "Blend (Hue)";
            }
            case BLEND_SATURATION: {
                return "Blend (Saturation)";
            }
            case BLEND_LUMINOSITY: {
                return "Blend (Luminosity)";
            }
            case BLEND_LINEAR_BURN: {
                return "Blend (Linear Burn)";
            }
            case BLEND_SOFT_LIGHT: {
                return "Blend (Soft Light)";
            }
            case BLEND_SUBTRACT: {
                return "Blend (Subtract)";
            }
            case BLEND_CHROMA_KEY: {
                return "Blend (Chroma Key)";
            }
            case BLEND_NORMAL: {
                return "Blend (Normal)";
            }
            case LOOKUP_AMATORKA: {
                return "Lookup (Amatorka)";
            }
            case GAUSSIAN_BLUR: {
                return "Gaussian Blur";
            }
            case CROSSHATCH: {
                return "Crosshatch";
            }
            case BOX_BLUR: {
                return "Box Blur";
            }
            case CGA_COLORSPACE: {
                return "CGA Color Space";
            }
            case DILATION: {
                return "Dilation";
            }
            case KUWAHARA: {
                return "Kuwahara";
            }
            case RGB_DILATION: {
                return "RGB Dilation";
            }
            case SKETCH: {
                return "Sketch";
            }
            case TOON: {
                return "Toon";
            }
            case SMOOTH_TOON: {
                return "Smooth Toon";
            }
            case BULGE_DISTORTION: {
                return "Bulge Distortion";
            }
            case GLASS_SPHERE: {
                return "Glass Sphere";
            }
            case HAZE: {
                return "Haze";
            }
            case LAPLACIAN: {
                return "Laplacian";
            }
            case NON_MAXIMUM_SUPPRESSION: {
                return "Non Maximum Suppression";
            }
            case SPHERE_REFRACTION: {
                return "Sphere Refraction";
            }
            case SWIRL: {
                return "Swirl";
            }
            case WEAK_PIXEL_INCLUSION: {
                return "Weak Pixel Inclusion";
            }
            case FALSE_COLOR: {
                return "False Color";
            }
            case COLOR_BALANCE: {
                return "Color Balance";
            }
            case LEVELS_FILTER_MIN: {
                return "Levels Min (Mid Adjust)";
            }
            case BILATERAL_BLUR: {
                return "Bilateral Blur";
            }
            case ZOOM_BLUR: {
                return "Zoom Blur";
            }
            case HALFTONE: {
                return "Halftone";
            }
            case TRANSFORM2D: {
                return "Transform (2-D)";
            }
            case SOLARIZE: {
                return "Solarize";
            }
            case VIBRANCE: {
                return "Vibrance";
            }
            default: {
                return "unknown";
            }
        }
    }
}
