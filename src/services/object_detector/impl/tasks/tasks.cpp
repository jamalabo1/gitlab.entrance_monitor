//
// Created by root on 10/2/22.
//
#include "tasks.h"

namespace object_detector::tasks {

    Components getObjectDetectorTasks() {
        return CORE_TASKS_CREATE_COMPONENT(ObjectDetector, DetectObjectsInStreamTask);
    }

}
