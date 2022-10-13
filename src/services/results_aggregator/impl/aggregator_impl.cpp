//
// Created by jamal on 13/08/2022.
//

#include "aggregator_impl.h"

#include <core/logging.h>
#include <cmath>

using namespace std;

namespace results_aggregator {

    namespace impl {

        AggregatorImpl::AggregatorImpl() = default;

        void AggregatorImpl::add(uint64_t x, int y) {
            a_sum += x * y;
            b_sum += x;
        }

        double AggregatorImpl::aggregate() {
            if (b_sum == 0) return 0;
            double avg = double(a_sum) / double(b_sum);
            BOOST_LOG_TRIVIAL(trace) << "avg: " << to_string(avg);
            reset();
            if (isnan(avg)) return 0;
            return avg;
        }

        void AggregatorImpl::reset() {
            a_sum = 0;
            b_sum = 0;
        }

    }

    AggregatorComponent getAggregatorComponent() {
        return fruit::createComponent()
                .bind<Aggregator, impl::AggregatorImpl>();
    }

};
