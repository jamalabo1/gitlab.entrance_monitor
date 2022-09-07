//
// Created by jamal on 03/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_OBJECT_DETECTOR_H
#define ENTRANCE_MONITOR_V2_OBJECT_DETECTOR_H

#include <core/core.h>

class ObjectDetector : public core::TaskService {
private:
    core::consume::Consumer *consumer;
    core::consume::ConsumerMessageHandler *handler;

public:
    INJECT(ObjectDetector(core::consume::Consumer * consumer,
                          core::consume::ConsumerMessageHandler * handler,
                          core::IoRunner* io_runner));


    int setup() override;
};


using ObjectDetectorComponent = fruit::Component<RequiredComponents, ObjectDetector>;

ObjectDetectorComponent getObjectDetectorComponent();

#endif //ENTRANCE_MONITOR_V2_OBJECT_DETECTOR_H
