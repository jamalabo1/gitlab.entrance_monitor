//
// Created by root on 10/4/22.
//

#ifndef ENTRANCE_MONITOR_V2_RESULTS_AGGREGATOR_AGGREGATE_BLOCKING_RESULTS_TASK_H
#define ENTRANCE_MONITOR_V2_RESULTS_AGGREGATOR_AGGREGATE_BLOCKING_RESULTS_TASK_H

#include <core/task.h>

#include "aggregator.h"

namespace results_aggregator::tasks {
    CORE_DEFINE_TASK_DEFAULT(ResultsAggregator, AggregateBlockingResultsTask, Aggregator);
}

#endif //ENTRANCE_MONITOR_V2_RESULTS_AGGREGATOR_AGGREGATE_BLOCKING_RESULTS_TASK_H
