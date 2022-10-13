//
// Created by root on 10/5/22.
//

#include "tasks.h"

using fruit::createComponent;

results_aggregator::tasks::Components results_aggregator::tasks::getResultsAggregatorTasks() {
    return createComponent()
            .registerProvider(MAKE_TASKS_PROVIDER(AggregateBlockingResultsTask, PublishAggregateResultsTask))
            .install(getAggregatorComponent)
            .install(getResultsAggregatorAggregateBlockingResultsTask)
            .install(getResultsAggregatorPublishAggregateResultsTask);
}