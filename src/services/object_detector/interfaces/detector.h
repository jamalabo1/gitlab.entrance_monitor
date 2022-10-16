//
// Created by jamal on 10/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_OBJECT_DETECTOR_DETECTOR_H
#define ENTRANCE_MONITOR_V2_OBJECT_DETECTOR_DETECTOR_H

#include <core/init.h>
#include <core/io_context.h>
#include <opencv2/core.hpp>
#include "detection_result.h"

namespace object_detector {

    class Detector {
    public:
        virtual DetectionResult detect_objects(const cv::Mat &) = 0;
    };

    using $Detector = $Exported<Detector>;
    using DetectorComponent = $Detector::PureComponent;

    DetectorComponent getDetectorComponent();
}

#endif //ENTRANCE_MONITOR_V2_OBJECT_DETECTOR_DETECTOR_H
