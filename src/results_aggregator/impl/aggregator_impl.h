//
// Created by jamal on 13/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_AGGREGATOR_IMPL_H
#define ENTRANCE_MONITOR_V2_AGGREGATOR_IMPL_H

#include <atomic>
#include "results_aggregator/aggregator.h"

class AggregatorImpl : public Aggregator {

private:
    std::atomic_uint64_t a_sum;
    std::atomic_uint64_t b_sum;

    void reset();

public:

    INJECT(AggregatorImpl());

    void add(uint64_t x, int y) override;

    double aggregate() override;

};


#endif //ENTRANCE_MONITOR_V2_AGGREGATOR_IMPL_H
