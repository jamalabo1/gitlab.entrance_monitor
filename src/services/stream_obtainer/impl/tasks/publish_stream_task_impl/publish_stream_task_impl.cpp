//
// Created by root on 9/29/22.
//
#include "publish_stream_task_impl.h"

#include <opencv2/imgproc.hpp>

#include <utils/mat.h>
#include <utils/reference_time.h>

#include <view_models/frame_view.h>


namespace stream_obtainer::tasks {

    using core::communication::publish::getCommunicationPublishComponents;

    namespace impl {

        using core::communication::publish::PublisherFactory;
        using core::communication::publish::Publisher;

        using std::string;
        using cv::Mat;
        using cv::Size;
        using utils::reference_time::getCurrentTimestamp;
        using utils::mat::mat_to_encoded_vector;

        using views::FrameView;

        PublishStreamTaskImpl::PublishStreamTaskImpl(FramesQueue *framesQueue,
                                                     PublisherFactory *publisherFactory)
                : queue_(framesQueue), publisher_factory_(publisherFactory) {

        }

        bool PublishStreamTaskImpl::configure() {
            BOOST_LOG_TRIVIAL(debug) << "[PublishStreamTaskImpl::configure]: configuring task";

            BOOST_LOG_TRIVIAL(trace) << "creating publisher from factory";
            // TODO: check if the publisher was created successfully. if not report.
            // create rabbitmq channel & connection
            publisher_ = publisher_factory_->create_publisher("frames.{1}");
            return publisher_ != nullptr;
        }

        core::Task::TaskResult PublishStreamTaskImpl::operator()() {
            // TODO: override the setup method to change the executor so it calls the task handle only when the queue is not empty.

            while (!queue_->empty()) {
                BOOST_LOG_TRIVIAL(trace) << "receiving frame from fpsQueue";
                Mat frame = queue_->get();

                if (frame.empty()) {
                    BOOST_LOG_TRIVIAL(trace) << "skipping empty frame";
                    continue;
                }

                cv::Mat resizedFrame;
                if (frame.size().width > 1920) {
                    BOOST_LOG_TRIVIAL(trace) << "resizing frame";
                    Size dsize(416, 416);
                    resize(frame, resizedFrame, dsize);
                } else {
                    resizedFrame = frame;
                }

                uint64_t currentTimestamp = getCurrentTimestamp();

                BOOST_LOG_TRIVIAL(trace) << "creating frame view";
                auto frameView = FrameView(mat_to_encoded_vector(resizedFrame), currentTimestamp);

                BOOST_LOG_TRIVIAL(trace) << "publishing frame with id " << string(frameView.id);
                publisher_->publish(
                        frameView
                );

                float fps = queue_->getFPS();
                BOOST_LOG_TRIVIAL(trace) << "queue_ fps: " << fps;
            }

            return TaskResult{};
        }

    }

    PublishStreamTaskComponent getStreamObtainerPublishStreamTask() {
        return CORE_TASK_CREATE_COMPONENT(PublishStreamTask)
                .install(getCommunicationPublishComponents);
    }

}

