//
// Created by jamal on 03/07/2022.
//

#include "object_detector/object_detector.h"

#include "tasks.h"

using fruit::createComponent;
using core::getCoreComponents;

using object_detector::tasks::getObjectDetectorTasks;

object_detector::ObjectDetectorService::ObjectDetectorService(const std::vector<shared_ptr<core::Task>> &tasks) {
    registerTasks(tasks);
}

object_detector::ObjectDetectorService::~ObjectDetectorService() = default;

object_detector::ObjectDetectorComponent object_detector::getObjectDetectorComponent() {
    return createComponent()
            .install(getObjectDetectorTasks)
            .install(getCoreComponents)
            .addMultibinding<core::Service, ObjectDetectorService>();
}
