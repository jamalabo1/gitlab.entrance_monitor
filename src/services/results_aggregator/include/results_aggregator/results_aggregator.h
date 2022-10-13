//
// Created by jamal on 13/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_RESULTS_AGGREGATOR_H
#define ENTRANCE_MONITOR_V2_RESULTS_AGGREGATOR_H

#include <core/core.h>

namespace results_aggregator {

class ResultsAggregatorService : public core::Service {
public:
    INJECT(ResultsAggregatorService(const std::vector<shared_ptr<core::Task>>& ));

    ~ResultsAggregatorService();
};

using $ResultsAggregatorService = $Exported<ResultsAggregatorService>;
using ResultAggregatorServiceComponent = $ResultsAggregatorService::PureComponent;
ResultAggregatorServiceComponent getResultsAggregatorServiceComponent();

}

#endif //ENTRANCE_MONITOR_V2_RESULTS_AGGREGATOR_H
