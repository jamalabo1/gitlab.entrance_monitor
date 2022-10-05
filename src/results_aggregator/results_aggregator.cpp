//
// Created by jamal on 13/08/2022.
//
#include "results_aggregator/results_aggregator.h"

#include "tasks.h"

using core::getCoreComponents;
using results_aggregator::tasks::getResultsAggregatorTasks;

results_aggregator::ResultsAggregatorService::ResultsAggregatorService
(const std::vector<shared_ptr<core::Task>> & tasks) {
    registerTasks(tasks);
}

results_aggregator::ResultsAggregatorService::~ResultsAggregatorService() = default;

results_aggregator::ResultAggregatorServiceComponent results_aggregator::getResultsAggregatorServiceComponent() {
    return fruit::createComponent()
            .install(getResultsAggregatorTasks)
            .install(getCoreComponents)
            .addMultibinding<core::Service, ResultsAggregatorService>();
}