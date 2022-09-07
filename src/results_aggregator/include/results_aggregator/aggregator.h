//
// Created by jamal on 13/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_AGGREGATOR_H
#define ENTRANCE_MONITOR_V2_AGGREGATOR_H

#include <cstdint>
#include <fruit/fruit.h>

class Aggregator {
public:
    virtual void add(uint64_t x, int y) = 0;

    virtual double aggregate() = 0;
};

using AggregatorComponent = fruit::Component<Aggregator>;

AggregatorComponent getAggregatorComponent();

#endif //ENTRANCE_MONITOR_V2_AGGREGATOR_H
