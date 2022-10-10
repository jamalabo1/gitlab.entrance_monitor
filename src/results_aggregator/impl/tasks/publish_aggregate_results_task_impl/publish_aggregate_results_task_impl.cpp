//
// Created by root on 10/4/22.
//

#include "publish_aggregate_results_task_impl.h"

#include <core/logging.h>

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


    token_ = std::move(token);

//    io_service_ = make_shared<boost::asio::io_service>();
//    auto timer_schedule = boost::posix_time::seconds(20);
//    timer_ = make_shared<boost::asio::deadline_timer>(*io_service_);

    auto default_executor = [=](const RunOptions::ExecutorCallback& cb) {
//        timer_->expires_from_now(timer_schedule);
//        timer_->async_wait([](const boost::system::error_code&) {
//            BOOST_LOG_TRIVIAL(fatal) << "not-fatal";
//        });
//        io_service_->run();
        // the default execution strategy is to loop until the operation is requested to cancel.
        auto timer_schedule = boost::posix_time::seconds(5);

        boost::asio::deadline_timer timer(GET_BOOST_IO_CONTEXT(ctx));

        timer.expires_from_now(timer_schedule);
        while(token_->isActive()) {
            BOOST_LOG_TRIVIAL(trace) << "waiting for timer.";
            timer.wait();
            BOOST_LOG_TRIVIAL(trace) << "finished waiting for timer.";
            cb();
            BOOST_LOG_TRIVIAL(trace) << "callback has been executed.";
            timer.expires_from_now(timer_schedule);
        }
    };
    return {
        default_executor
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