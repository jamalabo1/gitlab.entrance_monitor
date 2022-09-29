//
// Created by root on 9/29/22.
//

#ifndef ENTRANCE_MONITOR_V2_STREAM_OBTAINER_TASKS_PUBLISH_STREAM_TASK_H
#define ENTRANCE_MONITOR_V2_STREAM_OBTAINER_TASKS_PUBLISH_STREAM_TASK_H

#include <core/task.h>
#include "frames_queue.h"

namespace stream_obtainer::tasks {
    CORE_DEFINE_TASK_DEFAULT(StreamObtainer, PublishStreamTask, FramesQueue);
}


#endif //ENTRANCE_MONITOR_V2_STREAM_OBTAINER_TASKS_PUBLISH_STREAM_TASK_H
