//
// Created by jamal on 13/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_RESULTS_AGGREGATOR_AGGREGATOR_H
#define ENTRANCE_MONITOR_V2_RESULTS_AGGREGATOR_AGGREGATOR_H

#include <core/init.h>

namespace results_aggregator {

    class Aggregator {
    public:
        virtual void add(uint64_t x, int y) = 0;

        virtual double aggregate() = 0;
    };

    using $Aggregator = $Exported<Aggregator>;
    using AggregatorComponent = $Aggregator::PureComponent;

    AggregatorComponent getAggregatorComponent();


}

#endif //ENTRANCE_MONITOR_V2_RESULTS_AGGREGATOR_AGGREGATOR_H
