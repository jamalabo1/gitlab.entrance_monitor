//
// Created by root on 10/5/22.
//

#include "tasks.h"


namespace results_aggregator::tasks {

    Components getResultsAggregatorTasks() {
        return CORE_TASKS_CREATE_COMPONENT(ResultsAggregator, AggregateBlockingResultsTask, PublishAggregateResultsTask)
                .install(getAggregatorComponent);
    }
}
