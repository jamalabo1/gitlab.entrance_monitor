//
// Created by root on 10/2/22.
//

#include "detect_objects_in_stream_impl.h"

#include <core/msgpacker.h>
#include <core/logging.h>

#include <utils/reference_time.h>
#include <utils/mat.h>
#include <utils/uuid.h>

//#include <view_models/detection_result_view.h>
#include <view_models/detection_result_view.pb.h>

//#include <view_models/frame_view.h>
#include <view_models/frame_view.pb.h>


using namespace core::communication;


namespace object_detector::tasks {

    namespace impl {

        using std::vector;
        using std::string;

        using core::amqp::ArgsTable;

        using core::msgpacker::pb::unpack;
        using core::msgpacker::unpack_frame_mat;

        using utils::uuid::generateId;
        using utils::reference_time::getCurrentTimestamp;
        using utils::mat::mat_to_encoded_vector;


//        using views::FrameView;
        using views::FrameView;
        using views::DetectionResultObjectView;
        using views::DetectionResultView;

//        using views::DetectionResultObjectView;
//        using views::DetectionResultView;

        DetectObjectsInStreamTaskImpl::DetectObjectsInStreamTaskImpl(
                shared_ptr <object_detector::Detector> detector,
                shared_ptr <consume::Consumer> consumer,
                shared_ptr <publish::PublisherFactory> publisher_factory
        ) : consumer_(consumer), detector_(detector), publisher_factory_(publisher_factory), consume_options_(nullptr) {
        }

        bool DetectObjectsInStreamTaskImpl::configure() {
            ArgsTable args
                    {
                            {
                                    "x-message-ttl", 60000
                            }
                    };
            publisher_ = publisher_factory_->create_publisher("detections.{1}", args);
            return publisher_ != nullptr;
        }

        core::Task::RunOptions
        DetectObjectsInStreamTaskImpl::setup(
                shared_ptr <core::IoContext> io_context,
                shared_ptr <core::CancellationToken> token) {
            ArgsTable args = {
                    {"x-max-length", 5} // MAX ACCUMULATIVE QUEUE SIZE IS 5,
                    // This ~means the max latency in the _queue is 5 frames.
                    // but if the publisher publishes messages faster than the consumers consume it (if they are more than 5) its a problem.
            };
            // set up the consume options here.
            consume_options_ = make_unique<consume::ConsumeOptions>(
                    this,
                    token,
                    "frames.{1}",
                    args,
                    // this queue can be consumed by multiple consumers.
                    true
            );

            return CORE_TASK_RUN_OPTIONS_ONE_TIME;
        }

        core::Task::TaskResult
        DetectObjectsInStreamTaskImpl::operator()() {
            BOOST_LOG_TRIVIAL(trace) << "consume_options_== null ? " << (consume_options_ == nullptr);
            consumer_->consume(*consume_options_);
            return TaskResult{};

        }

        void DetectObjectsInStreamTaskImpl::operator()(
                const consume::ConsumerMessage::ptr_t &envelope) const {
            BOOST_LOG_TRIVIAL(trace)
            << "[detect_objects_in_stream::impl::DetectObjectsInStreamTaskImpl::operator()]: message received";

            auto frameView = unpack<FrameView>(envelope);


            BOOST_LOG_TRIVIAL(trace) << "received frame with id " << frameView.id();
            auto frame = unpack_frame_mat(frameView);

            auto result = detector_->detect_objects(frame);

            BOOST_LOG_TRIVIAL(trace) << "detected " << result.ids.size() << " objects in frame with id "
                                     << frameView.id();


            DetectionResultView result_view;
            result_view.set_id(generateId());
            result_view.set_frame_id(frameView.id());
            result_view.set_timestamp(getCurrentTimestamp());

            // set the dimensions of the received frame for dynamic processing.
            result_view.add_frame_dimensions(frame.size().width);
            result_view.add_frame_dimensions(frame.size().height);

            for (size_t i = 0; i < result.confidences.size(); i++) {
                int classId = result.ids[i];

                if (classId != 2 && classId != 7) {
                    continue;
                }

                int8_t conf = (result.confidences[i] * 100);

                auto box = result.boxes[i];
                auto object_view = result_view.add_objects();

                // add frame view object
                auto object_frame_view = object_view->mutable_object();

                // set only the frame data of the object for further computation
                object_frame_view->set_frame_data(utils::mat::mat_to_encoded_string(frame(box)));

                // set the dimensions of the box of the detection.
                for (auto val: {box.x, box.y, box.width, box.height}) {
                    object_view->add_box(val);
                }

                // set the confidence of the detection
                object_view->set_confidence(conf);

                // set the classId of the detection
                object_view->set_classid(classId);
            }

            // publish the results.
            publisher_->publish_pb(result_view);
        }
    }

    DetectObjectsInStreamTaskComponent getObjectDetectorDetectObjectsInStreamTask() {
        return CORE_TASK_CREATE_COMPONENT(DetectObjectsInStreamTask)
                .install(getDetectorComponent)
                .install(getCommunicationComponents);
    }
}
