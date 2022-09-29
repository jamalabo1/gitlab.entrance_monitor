//
// Created by jamal on 29/09/2022.
//

#ifndef ENTRANCE_MONITOR_V2_STREAM_OBTAINER_INTERFACES_TASKS_H
#define ENTRANCE_MONITOR_V2_STREAM_OBTAINER_INTERFACES_TASKS_H

#include <core/init.h>
#include "tasks/subscribe_to_stream_task.h"

namespace stream_obtainer::tasks {
    EXPORT_MODULE(getStreamObtainerTasks, $SubscribeToStreamTask);
}

#endif //ENTRANCE_MONITOR_V2_STREAM_OBTAINER_INTERFACES_TASKS_H
