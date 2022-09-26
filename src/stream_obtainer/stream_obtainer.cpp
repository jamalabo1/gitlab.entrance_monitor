//
// Created by jamal on 28/05/2022.
//

#include <core/logging.h>

#include <utils/mat.h>
#include <utils/reference_time.h>
#include <utils/service.h>

#include <stream_obtainer/stream_obtainer.h>
#include "stream_subscriber.h"
#include <view_models/frame_view.h>

#include <opencv2/imgproc.hpp>

using namespace std;
using namespace fruit;
using namespace cv;
using namespace core;
using namespace core::communication::publish;


StreamObtainer::StreamObtainer(
        PublisherFactory *publisher_factory,
        IoRunner *io_runner,
        Configurations *configurations
) : Service(io_runner), publisher_factory(publisher_factory), configs(configurations) {

}

int StreamObtainer::setup() {
    BOOST_LOG_TRIVIAL(info) << "running stream obtainer service";

    shared_ptr<FramesQueue> queue = make_shared<FramesQueue>();

    auto url = configs->get("camera-stream-url");

    BOOST_LOG_TRIVIAL(debug) << "creating stream subscriber thread";

    // run in another process, so that publishing messages is not blocking the frames VideoCapture.
    post(bind(&subscribe_to_stream, url, std::ref(queue)));

    BOOST_LOG_TRIVIAL(debug) << "creating publisher from factory";

    // create rabbitmq channel & connection
    shared_ptr<Publisher> publisher = publisher_factory->create_publisher("frames.{1}");

    post([&]() {
        BOOST_LOG_TRIVIAL(trace) << "setting up stream publisher";
        for (;;) {
            if (queue->empty()) continue;
            cv::Mat frame = queue->get();
            BOOST_LOG_TRIVIAL(trace) << "receiving frame from fpsQueue";

            if (frame.empty()) {
                BOOST_LOG_TRIVIAL(trace) << "skipping empty frame";
                continue;
            }

            cv::Mat resizedFrame;
            if (frame.size().width > 1920) {
                Size dsize(416, 416);
                resize(frame, resizedFrame, dsize);
            } else {
                resizedFrame = frame;
            }

            uint64_t currentTimestamp = getCurrentTimestamp();

            auto frameView = FrameView(mat_to_encoded_vector(resizedFrame), currentTimestamp);

            BOOST_LOG_TRIVIAL(trace) << "publishing frame with id " << string(frameView.id);

            publisher->publish(
                    frameView
            );

            float fps = queue->getFPS();
            BOOST_LOG_TRIVIAL(trace) << "_queue fps: " << fps;
        }
    });

    return run();
}


StreamObtainer::~StreamObtainer() {
    BOOST_LOG_TRIVIAL(info) << "quitting stream obtainer service";
}


StreamObtainerComponent getStreamObtainerComponent() {
    return createComponent()
            .install(getCoreComponents)
            .addMultibinding<Service, StreamObtainer>();
}
