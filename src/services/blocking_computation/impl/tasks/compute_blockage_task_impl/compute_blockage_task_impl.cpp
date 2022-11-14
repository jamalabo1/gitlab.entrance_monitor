//
// Created by root on 10/5/22.
//

#include "compute_blockage_task_impl.h"

#include <boost/thread.hpp>

#include <core/logging.h>

#include <view_models/blocking_result_view.pb.h>
#include <view_models/detection_result_view.pb.h>

#include "match_to_shape.h"
#include "compute_intersection.h"

namespace blocking_computation::tasks {

    namespace impl {
        // types
        using std::vector;
        using cv::Size;
        using cv::Point;
        using core::amqp::ArgsTable;
        using core::communication::consume::ConsumeOptions;

        //
        using core::msgpacker::pb::unpack;

        // views
        using views::DetectionResultView;
        using views::BlockingResultView;

        // utils
        using utils::match_to_shape;
        using utils::compute_intersection;

        ComputeBlockageTaskImpl::ComputeBlockageTaskImpl(
                shared_ptr<core::communication::publish::PublisherFactory> publisher_factory,
                shared_ptr<core::communication::consume::Consumer> consumer
        ) : publisher_factory_(publisher_factory), consumer_(consumer), consume_options_(nullptr) {

        }

        core::Task::RunOptions ComputeBlockageTaskImpl::setup(shared_ptr<core::IoContext> ctx,
                                                              shared_ptr<core::CancellationToken> token) {
            ArgsTable args = {
                    {"x-max-length", 5} // MAX ACCUMULATIVE QUEUE SIZE IS 5,
                    // This ~means the max latency in the _queue is 5 frames.
                    // but if the publisher publishes messages faster than the consumers consume it (if they are more than 5) its a problem.
            };
            // set up the consume options here.
            consume_options_ = make_unique<ConsumeOptions>(
                    this,
                    token,
                    "detections.{1}",
                    args,
                    // this queue can be consumed by multiple consumers.
                    true
            );

            return CORE_TASK_RUN_OPTIONS_ONE_TIME;
        }

        bool ComputeBlockageTaskImpl::configure() {
            publisher_ = publisher_factory_->create_publisher("blocking.{1}");
            return publisher_ != nullptr;
        }

        core::Task::TaskResult ComputeBlockageTaskImpl::operator()() {
            consumer_->consume(*consume_options_);
            return TaskResult{};
        }

        void ComputeBlockageTaskImpl::operator()(
                const core::communication::consume::ConsumerMessage::ptr_t &envelope) const {

            static auto original_shape = Size(1920, 1080);
            static auto bounding_points = vector<Point>{
                    Point(1920, 650),
                    Point(826, 1080),
                    Point(573, 700),
                    Point(1114, 508),
                    Point(1403, 476),
            };
            auto detectionResultView = unpack<DetectionResultView>(envelope);


            BOOST_LOG_TRIVIAL(trace) << "received detection result with " << detectionResultView.objects_size()
                                     << " objects and frame-width: " << detectionResultView.frame_dimensions(0);


            auto frame_dimension = Size(detectionResultView.frame_dimensions(0),
                                        detectionResultView.frame_dimensions(1));

            auto relative_points = match_to_shape(bounding_points, original_shape, frame_dimension);


            std::atomic_int results_count = 0;

            boost::thread_group pool;

            BOOST_LOG_TRIVIAL(trace) << "looping over detected objects";

            for (auto i = 0; i < detectionResultView.objects_size(); i++) {
                BOOST_LOG_TRIVIAL(trace) << "creating thread for the object n." << i;
                //obj, &frame_dimension, &results_count, &relative_points
                pool.create_thread([&, i]() {
                    auto obj = detectionResultView.objects(i);

                    BOOST_LOG_TRIVIAL(trace) << "computing the intersection for the object n." << i;

                    auto result = compute_intersection(obj, frame_dimension, relative_points);

                    BOOST_LOG_TRIVIAL(trace) << "intersection computing result: " << result.has_value();
                    if (result.has_value() && result.get()) {
                        results_count++;
                        // no need to resume the computation since the requirement is at-least one blocking object.
                        // and since we can ignore the number of blocking objects we can safely interrupt the other thread after we found at least on blocking object.
                        pool.interrupt_all();
                    }
                });
            }

            try {
                pool.join_all();
            } catch (...) {
                // TODO: proper handling, the current exception ignoring is for interrupting the threads.
            }

            BlockingResultView blocking_result;

            blocking_result.set_result(results_count > 0);
            blocking_result.set_timestamp(detectionResultView.timestamp());

            publisher_->publish_pb(blocking_result);
        }
    } // impl

    ComputeBlockageTaskComponent
    getBlockingComputationComputeBlockageTask() {
        return CORE_TASK_CREATE_COMPONENT(ComputeBlockageTask)
                .install(core::communication::getCommunicationComponents);
    }
}

