//
// Created by root on 10/4/22.
//

#ifndef ENTRANCE_MONITOR_V2_RESULTS_AGGREGATOR_AGGREGATE_BLOCKING_RESULTS_TASK_IMPL_H
#define ENTRANCE_MONITOR_V2_RESULTS_AGGREGATOR_AGGREGATE_BLOCKING_RESULTS_TASK_IMPL_H

#include "tasks/aggregate_blocking_results_task.h"

#include <core/communication/consume.h>

namespace results_aggregator::tasks::impl {
    class AggregateBlockingResultsTaskImpl :
            public AggregateBlockingResultsTask,
            public core::communication::consume::ConsumerMessageHandler {
    private:
        unique_ptr<core::communication::consume::ConsumeOptions> consume_options_;
        shared_ptr<core::communication::consume::Consumer> consumer_;

        shared_ptr<results_aggregator::Aggregator> aggregator_;

    public:

        INJECT(AggregateBlockingResultsTaskImpl(
                shared_ptr<core::communication::consume::Consumer>,
                shared_ptr<results_aggregator::Aggregator>
        ));

        void operator()(const core::communication::consume::ConsumerMessage::ptr_t &envelope) const override;

        RunOptions setup(shared_ptr<core::IoContext> ptr, shared_ptr<core::CancellationToken> sharedPtr) override;

        TaskResult operator()() override;
    };
}

#endif //ENTRANCE_MONITOR_V2_RESULTS_AGGREGATOR_AGGREGATE_BLOCKING_RESULTS_TASK_IMPL_H
