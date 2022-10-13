//
// Created by root on 10/5/22.
//

#ifndef ENTRANCE_MONITOR_V2_TASKS_H
#define ENTRANCE_MONITOR_V2_TASKS_H

#include <core/init.h>

#include "tasks/compute_blockage_task.h"

namespace blocking_computation::tasks {
    EXPORT_TASKS_MODULE(getBlockingComputationTasks, $ComputeBlockageTask);
}

#endif //ENTRANCE_MONITOR_V2_TASKS_H
