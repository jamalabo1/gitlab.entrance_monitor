//
// Created by root on 10/2/22.
//
#include "tasks.h"

using fruit::createComponent;

object_detector::tasks::Components object_detector::tasks::getObjectDetectorTasks() {
    return createComponent()
            .registerProvider(MAKE_TASKS_PROVIDER(detect_objects_in_stream::DetectObjectsInStreamTask))
            .install(detect_objects_in_stream::getObjectDetectorDetectObjectsInStreamTask);
}