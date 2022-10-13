//
// Created by root on 10/2/22.
//

#ifndef ENTRANCE_MONITOR_V2_OBJECT_DETECTOR_TASKS_H
#define ENTRANCE_MONITOR_V2_OBJECT_DETECTOR_TASKS_H

#include <core/init.h>

#include "tasks/detect_objects_in_stream_task.h"

namespace object_detector::tasks {
    EXPORT_TASKS_MODULE(getObjectDetectorTasks, detect_objects_in_stream::$DetectObjectsInStreamTask);
}

#endif //ENTRANCE_MONITOR_V2_OBJECT_DETECTOR_TASKS_H
