//
// Created by root on 10/5/22.
//

#ifndef ENTRANCE_MONITOR_V2_RESULTS_AGGREGATOR_TASKS_H
#define ENTRANCE_MONITOR_V2_RESULTS_AGGREGATOR_TASKS_H

#include <core/init.h>

#include "tasks/aggregate_blocking_results_task.h"
#include "tasks/publish_aggregate_results_task.h"

namespace results_aggregator::tasks {
    EXPORT_TASKS_MODULE(getResultsAggregatorTasks, $AggregateBlockingResultsTask, $PublishAggregateResultsTask);
}

#endif //ENTRANCE_MONITOR_V2_RESULTS_AGGREGATOR_TASKS_H
