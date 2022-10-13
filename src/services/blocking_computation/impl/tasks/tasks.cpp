//
// Created by root on 10/5/22.
//
#include "tasks.h"

namespace blocking_computation::tasks {

    Components getBlockingComputationTasks() {
        return CORE_TASKS_CREATE_COMPONENT(BlockingComputation, ComputeBlockageTask);
    }

}