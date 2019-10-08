//
// Created by ben622 on 2019/10/8.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_THRESHOLD_EDGE_DETECTION_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_THRESHOLD_EDGE_DETECTION_FILTER_HPP

#include "gpu_image_filter_group.hpp"
#define JAVA_THRESHOLD_EDGE_DETECTION_FILTER "com/ben/android/library/filter/GPUImageThresholdEdgeDetectionFilter"
namespace ben{
    namespace ngp{
        class GPUImageThresholdEdgeDetectionFilter:public GPUImageFilterGroup{
        private:
            float size;
            float threshold;
        public:
            GPUImageThresholdEdgeDetectionFilter();

            GPUImageThresholdEdgeDetectionFilter(JNIEnv *env);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            float getSize() const;

            void setSize(float size);

            float getThreshold() const;

            void setThreshold(float threshold);

        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_THRESHOLD_EDGE_DETECTION_FILTER_HPP
