//
// Created by root on 10/4/22.
//

#include "aggregate_blocking_results_task_impl.h"

#include <core/logging.h>
#include <core/msgpacker.h>

#include <view_models/blocking_result_view.h>


using namespace core::communication;
using results_aggregator::Aggregator;

using core::msgpacker::unpack;
using views::BlockingResultView;

results_aggregator::tasks::impl::AggregateBlockingResultsTaskImpl::AggregateBlockingResultsTaskImpl(
        shared_ptr<consume::Consumer> consumer,
        shared_ptr<Aggregator> aggregator
) : aggregator_(aggregator), consumer_(consumer), consume_options_(nullptr) {}

core::Task::RunOptions
results_aggregator::tasks::impl::AggregateBlockingResultsTaskImpl::setup(shared_ptr<core::IoContext> ctx,
                                                                         shared_ptr<core::CancellationToken> token) {
    // set up the consume options here.
    consume_options_ = make_unique<consume::ConsumeOptions>(
            shared_from_this(),
            token,
            "blocking.{1}"
    );

    return CORE_TASK_RUN_OPTIONS_ONE_TIME;
}

core::Task::TaskResult results_aggregator::tasks::impl::AggregateBlockingResultsTaskImpl::operator()() {
    consumer_->consume(*consume_options_);
}

void results_aggregator::tasks::impl::AggregateBlockingResultsTaskImpl::operator()(
        const core::communication::consume::ConsumerMessage::ptr_t &envelope) const {

    auto view = unpack<BlockingResultView>(envelope);

    BOOST_LOG_TRIVIAL(trace) << "received blocking result: " << view.result << " on timestamp " << view.frame_timestamp;

    aggregator_->add(view.frame_timestamp, view.result);
}

results_aggregator::tasks::AggregateBlockingResultsTaskComponent results_aggregator::tasks::getResultsAggregatorAggregateBlockingResultsTask() {
 return fruit::createComponent()
            .install(consume::getCommunicationConsumeComponents)
            .bind<AggregateBlockingResultsTask, impl::AggregateBlockingResultsTaskImpl>()
            .addMultibinding<core::Task, impl::AggregateBlockingResultsTaskImpl>();
}