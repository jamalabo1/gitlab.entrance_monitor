//
// Created by root on 10/4/22.
//

#include "publish_aggregate_results_task_impl.h"

#include <core/logging.h>

#include <utils/uuid.h>

#include <view_models/computed_result_view.pb.h>

namespace results_aggregator::tasks {
    namespace impl {

        using std::function;
        using views::ComputedResultView;
        using utils::uuid::generateId;

        PublishAggregateResultsTaskImpl::PublishAggregateResultsTaskImpl(
                shared_ptr<core::communication::publish::PublisherFactory>
                publisher_factory,
                shared_ptr<Aggregator> aggregator
        ) : publisher_factory_(publisher_factory), aggregator_(aggregator) {

        }

        bool PublishAggregateResultsTaskImpl::configure() {
            publisher_ = publisher_factory_->create_publisher("results.{1}");
            return publisher_ != nullptr;
        }

        core::Task::RunOptions
        PublishAggregateResultsTaskImpl::setup(shared_ptr<core::IoContext> ctx,
                                               shared_ptr<core::CancellationToken>
                                               token) {
            token_ = std::move(token);

            auto default_executor = [=](const RunOptions::ExecutorCallback &cb) {
                // the default execution strategy is to loop until the operation is requested to cancel.
                auto timer_schedule = boost::posix_time::seconds(5);

                boost::asio::deadline_timer timer(GET_BOOST_IO_CONTEXT(ctx));

                timer.expires_from_now(timer_schedule);
                while (token_->isActive()) {
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

        core::Task::TaskResult PublishAggregateResultsTaskImpl::operator()() {
            double result = aggregator_->aggregate();
            ComputedResultView view;

            view.set_id(generateId());
            view.set_is_blocking(result > 0.5);

            publisher_->publish_pb(view);
            return TaskResult{};
        }
    }


    PublishAggregateResultsTaskComponent
    getResultsAggregatorPublishAggregateResultsTask() {
        return CORE_TASK_CREATE_COMPONENT(PublishAggregateResultsTask)
                .install(core::communication::publish::getCommunicationPublishComponents);
    }
}
