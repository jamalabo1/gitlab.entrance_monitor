//
// Created by jamal on 10/08/2022.
//
#include "frame_message_handler.h"
#include "utils/mat.h"

#include <core/msgpacker.h>
#include <core/logging.h>

#include <utils/reference_time.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>

#include <view_models/detection_result_view.h>

#include <boost/format.hpp>

using namespace cv;
using namespace std;
using namespace fruit;
using namespace core;
using namespace core::consume;
using namespace core::communication::publish;
using namespace core::msgpacker;
using namespace core::amqp;


FrameMessageHandler::FrameMessageHandler(Detector *detector, PublisherFactory *publisher_factory,
                                         core::GUIHandler *gui_handler) : detector(detector), gui_handler(gui_handler) {
    ArgsTable args
            {
                    {
                            "x-message-ttl", 60000
                    }
            };
    publisher = publisher_factory->create_publisher("detections.{1}", args);
}

void FrameMessageHandler::operator()(const ConsumerMessage::ptr_t &message) const {


    static const vector<int> allowed_class_ids = {2, 7};

    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_VERBOSE);
//    BOOST_LOG_TRIVIAL(debug) << "message_callback on envelope" << envelope->ConsumerTag()
//                             << envelope->Message()->AppId();

    auto frameView = core::msgpacker::unpack<FrameView>(message);


    BOOST_LOG_TRIVIAL(trace) << "received frame with id " << string(frameView.id);
    Mat frame = unpack_frame_mat(frameView);

    auto result = detector->detect_objects(frame);

    vector<DetectionResultObjectView> object_views;

    for (size_t i = 0; i < result.confidences.size(); i++) {
        int classId = result.ids[i];

        if (!binary_search(allowed_class_ids.begin(), allowed_class_ids.end(), classId)) {
            continue;
        }

        int8_t conf = (result.confidences[i] * 100);

        Rect box = result.boxes[i];
        FrameView object(mat_to_encoded_vector(frame(box)), getCurrentTimestamp());
        vector<int> box_vector = {box.x, box.y, box.width, box.height};
        object_views.emplace_back(
                DetectionResultObjectView(
                        object,
                        conf,
                        classId,
                        box_vector
                )
        );


#ifdef APP_DEBUG
        string text = str(boost::format("%1%5.2f it's a %2%") % conf % classId);
        putText(
                frame,
                text,
                Point(box.x - 10, box.y - 10),
                1,
                1,
                Scalar(0, 255)
        );

        rectangle(
                frame,
                box,
                Scalar(255)
        );
#endif

    }

    vector<int> frame_dimension = {frame.size().width, frame.size().height};
    auto resultView = DetectionResultView(frameView.id, frameView.timestamp, object_views, frame_dimension);

    publisher->publish(resultView);


#ifdef APP_DEBUG
    gui_handler->imshow("frame", frame);
#endif
}


FrameMessageHandlerComponent getFrameMessageHandlerComponent() {
    return createComponent()
            .install(getDetectorComponent)
            .bind<ConsumerMessageHandler, FrameMessageHandler>();
}