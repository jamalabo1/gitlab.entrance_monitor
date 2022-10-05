//
// Created by root on 10/5/22.
//
#include "tasks.h"

namespace blocking_computation::tasks {
    using fruit::createComponent;

    Components getBlockingComputationTasks() {
        return createComponent()
                .registerProvider(MAKE_TASKS_PROVIDER(ComputeBlockageTask))
                .install(getBlockingComputationComputeBlockageTask);
    }
}