//
// Created by root on 10/4/22.
//

#ifndef ENTRANCE_MONITOR_V2_PUBLISH_AGGREGATE_RESULTS_TASK_IMPL_H
#define ENTRANCE_MONITOR_V2_PUBLISH_AGGREGATE_RESULTS_TASK_IMPL_H

#include "tasks/publish_aggregate_results_task.h"

#include <core/communication/publish.h>

namespace results_aggregator::tasks::impl {
    class PublishAggregateResultsTaskImpl : public PublishAggregateResultsTask {
    private:
        shared_ptr<core::communication::publish::PublisherFactory> publisher_factory_;
        unique_ptr<core::communication::publish::Publisher> publisher_;

        shared_ptr<Aggregator> aggregator_;

        shared_ptr<boost::asio::io_service> io_service_;
        shared_ptr<boost::asio::deadline_timer> timer_;

    public:
        INJECT(PublishAggregateResultsTaskImpl(
                shared_ptr<core::communication::publish::PublisherFactory>,
                shared_ptr<Aggregator>
        ));

        RunOptions setup(shared_ptr<core::IoContext> ptr, shared_ptr<core::CancellationToken> sharedPtr) override;

        bool configure() override;

        TaskResult operator()() override;
    };
}

#endif //ENTRANCE_MONITOR_V2_PUBLISH_AGGREGATE_RESULTS_TASK_IMPL_H
