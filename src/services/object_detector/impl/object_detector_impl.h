//
// Created by jamal on 10/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_OBJECT_DETECTOR_DETECTOR_IMPL_H
#define ENTRANCE_MONITOR_V2_OBJECT_DETECTOR_DETECTOR_IMPL_H


#include "detector.h"
#include <opencv2/dnn.hpp>


namespace object_detector::impl {

    class DetectorImpl : public Detector {
    private:
        void prepare_model();

        core::Configurations *configs;
        unique_ptr<cv::dnn::DetectionModel> detectionModel_;

    public:
        INJECT(DetectorImpl(core::Configurations * configurations));

        DetectionResult detect_objects(const cv::Mat &) override;
    };
}


#endif //ENTRANCE_MONITOR_V2_OBJECT_DETECTOR_DETECTOR_IMPL_H
