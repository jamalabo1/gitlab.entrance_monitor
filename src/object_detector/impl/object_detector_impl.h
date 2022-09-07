//
// Created by jamal on 10/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_OBJECT_DETECTOR_IMPL_H
#define ENTRANCE_MONITOR_V2_OBJECT_DETECTOR_IMPL_H


#include "detector.h"
#include <opencv2/dnn.hpp>


class DetectorImpl : public Detector {
private:
    void prepare_model();

    core::Configurations *configs;
    shared_ptr<cv::dnn::DetectionModel> detection_model;

    std::mutex detection_model_mutex;

public:
    INJECT(DetectorImpl(core::Configurations * configurations, core::IoRunner* io_runner));

    DetectionResult detect_objects(const cv::Mat &) override;
};


#endif //ENTRANCE_MONITOR_V2_OBJECT_DETECTOR_IMPL_H
