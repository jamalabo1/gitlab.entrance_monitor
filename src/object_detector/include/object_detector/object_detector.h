//
// Created by jamal on 03/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_OBJECT_DETECTOR_H
#define ENTRANCE_MONITOR_V2_OBJECT_DETECTOR_H

#include <core/core.h>

namespace object_detector {

class ObjectDetectorService : public core::Service {
public:
    INJECT(ObjectDetectorService(const std::vector<shared_ptr<core::Task>>& ));

    ~ObjectDetectorService();
};


    using $ObjectDetector = $Exported<ObjectDetectorService>;
    using ObjectDetectorComponent = $ObjectDetector::PureComponent;

    ObjectDetectorComponent getObjectDetectorComponent();
}

#endif //ENTRANCE_MONITOR_V2_OBJECT_DETECTOR_H
