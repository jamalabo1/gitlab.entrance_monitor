//
// Created by jamal on 13/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_RESULTS_AGGREGATOR_H
#define ENTRANCE_MONITOR_V2_RESULTS_AGGREGATOR_H

#include <core/core.h>

#include "aggregator.h"

class ResultsAggregatorService : public core::TaskService {
private:
    core::consume::Consumer *consumer;
    core::consume::ConsumerMessageHandler *handler;
    unique_ptr<core::publish::Publisher> publisher;
    Aggregator *aggregator;

public:
    INJECT(ResultsAggregatorService(
            core::consume::Consumer * consumer,
            core::consume::ConsumerMessageHandler * handler,
            core::publish::PublisherFactory * publisher_factory,
            core::IoRunner * io_runner,
            Aggregator * aggregator
    )
    );


    int setup() override;

protected:
    void graph_computation();
};

using ResultAggregatorServiceComponent = fruit::Component<RequiredComponents, ResultsAggregatorService>;

ResultAggregatorServiceComponent getResultsAggregatorServiceComponent();


#endif //ENTRANCE_MONITOR_V2_RESULTS_AGGREGATOR_H
