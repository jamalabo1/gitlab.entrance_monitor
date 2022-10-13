//
// Created by jamal on 13/08/2022.
//
#include "results_aggregator/results_aggregator.h"

#include "tasks.h"


namespace results_aggregator {

    using core::getCoreComponents;
    using tasks::getResultsAggregatorTasks;

    ResultsAggregatorService::ResultsAggregatorService
            (const std::vector<shared_ptr<core::Task>> &tasks) {
        registerTasks(tasks);
    }

    ResultsAggregatorService::~ResultsAggregatorService() = default;

    ResultAggregatorServiceComponent getResultsAggregatorServiceComponent() {
        return fruit::createComponent()
                .install(getResultsAggregatorTasks)
                .install(getCoreComponents)
                .addMultibinding<core::Service, ResultsAggregatorService>();
    }
}

