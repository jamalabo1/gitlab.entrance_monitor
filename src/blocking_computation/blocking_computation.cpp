//
// Created by jamal on 13/08/2022.
//

#include "blocking_computation/blocking_computation.h"

#include "tasks.h"

namespace blocking_computation {

    using fruit::createComponent;
    using core::Service;
    using core::getCoreComponents;
    using tasks::getBlockingComputationTasks;

    BlockingComputationService::BlockingComputationService(
            const std::vector<shared_ptr<core::Task>> &tasks) {
        registerTasks(tasks);
    }

BlockingComputationComponent getBlockingComputationComponent() {
    return createComponent()
            .install(getCoreComponents)
            .install(getBlockingComputationTasks)
            .addMultibinding<Service, BlockingComputationService>();
}



}
