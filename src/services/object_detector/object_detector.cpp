//
// Created by jamal on 03/07/2022.
//

#include "object_detector/object_detector.h"

#include "tasks.h"


namespace object_detector {

    using fruit::createComponent;
    using core::getCoreComponents;
    using tasks::getObjectDetectorTasks;

    ObjectDetectorService::ObjectDetectorService(const std::vector<shared_ptr<core::Task>> &tasks) {
        registerTasks(tasks);
    }

    ObjectDetectorService::~ObjectDetectorService() = default;

    ObjectDetectorComponent getObjectDetectorComponent() {
        return createComponent()
                .install(getObjectDetectorTasks)
                .install(getCoreComponents)
                .addMultibinding<core::Service, ObjectDetectorService>();
    }

}
