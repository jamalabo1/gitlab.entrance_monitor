//
// Created by root on 10/4/22.
//

#include "publish_aggregate_results_task_impl.h"

#include <view_models/computed_result_view.h>

using std::function;
using views::ComputedResultView;

results_aggregator::tasks::impl::PublishAggregateResultsTaskImpl::PublishAggregateResultsTaskImpl(
        shared_ptr<core::communication::publish::PublisherFactory> publisher_factory,
        shared_ptr<Aggregator> aggregator
) : publisher_factory_(publisher_factory), aggregator_(aggregator) {

}


core::Task::RunOptions
results_aggregator::tasks::impl::PublishAggregateResultsTaskImpl::setup(shared_ptr<core::IoContext> ctx,
                                                                        shared_ptr<core::CancellationToken> token) {

    auto timer_schedule = boost::asio::chrono::seconds(5);
    timer_ = make_unique<boost::asio::steady_timer>(GET_BOOST_IO_CONTEXT(ctx), timer_schedule);

    return RunOptions{
        .executor=[this, timer_schedule](auto cb) {
            function<void(const boost::system::error_code &)> fn;

            // TODO: replace this with the coming feature of `io_runner` `IoRunner::schedule`
            fn = [this, &fn, &timer_schedule, cb](const boost::system::error_code &ec) {
                cb();
                timer_->expires_from_now(timer_schedule);
                timer_->async_wait(fn);
            };
            timer_->async_wait(fn);
        }
    };
}

bool results_aggregator::tasks::impl::PublishAggregateResultsTaskImpl::configure() {
    publisher_ = publisher_factory_->create_publisher("results.{1}");
}

core::Task::TaskResult results_aggregator::tasks::impl::PublishAggregateResultsTaskImpl::operator()() {
    double result = aggregator_->aggregate();
    ComputedResultView view(result > 0.5);

    publisher_->publish(view);
}

results_aggregator::tasks::PublishAggregateResultsTaskComponent results_aggregator::tasks::getResultsAggregatorPublishAggregateResultsTask() {
    return fruit::createComponent()
            .install(core::communication::publish::getCommunicationPublishComponents)
            .bind<PublishAggregateResultsTask, impl::PublishAggregateResultsTaskImpl>()
            .addMultibinding<core::Task, impl::PublishAggregateResultsTaskImpl>();
}