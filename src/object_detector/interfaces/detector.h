//
// Created by jamal on 10/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_DETECTOR_H
#define ENTRANCE_MONITOR_V2_DETECTOR_H

#include <core/init.h>
#include <core/io_runner.h>
#include <opencv2/core.hpp>
#include "detection_result.h"

class Detector {

public:
    virtual DetectionResult detect_objects(const cv::Mat &) = 0;
};

using DetectorComponent = fruit::Component<MakeRequiredComponents(core::IoRunner), Detector>;

DetectorComponent getDetectorComponent();

#endif //ENTRANCE_MONITOR_V2_DETECTOR_H
