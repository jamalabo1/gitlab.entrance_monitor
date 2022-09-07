//
// Created by jamal on 02/07/2022.
//

#include "stream_subscriber.h"

#include <core/logging.h>

#include <opencv2/videoio.hpp>
#include <opencv2/core/utils/logger.hpp>

#include <boost/asio.hpp>

using namespace std;
using namespace cv;

unique_ptr<VideoCapture> create_capture() {
    BOOST_LOG_TRIVIAL(trace) << "creating `cv::VideoCapture`";
    return make_unique<VideoCapture>();
}

void subscribe_to_stream(const string &stream_url, shared_ptr<FramesQueue> &queue) {
    BOOST_LOG_TRIVIAL(info) << "subscribing to stream";
    BOOST_LOG_TRIVIAL(trace) << "setting openCV logging level";
    utils::logging::setLogLevel(utils::logging::LOG_LEVEL_VERBOSE);

    unique_ptr<VideoCapture> cap = create_capture();

    BOOST_LOG_TRIVIAL(debug) << "opening `VideoCapture` stream";
    cap->open(stream_url);


    atomic_bool is_stream_running = true;

    auto stop_stream_loop = [&is_stream_running]() {
        // this sets the `is_stream_running` to false, which stops the stream obtaining loop
        is_stream_running = false;
    };

    atomic_int failed_retry_count;

    auto increase_failed_count = [&failed_retry_count]() {
        failed_retry_count++;
    };
    auto reset_failed_count = [&failed_retry_count]() {
        failed_retry_count = 0;
    };

    // pre-define a `schedule_retry_handler`, so it can be called from inside `retry_handler`
    function<void()> schedule_retry_handler;

    // capture lock, to ensure that `retry_handler` does not overwrite an in-use `capture`.
    mutex cap_lock;

    auto retry_duration = boost::posix_time::seconds(30);
    // retry handler. locks the `cap` and creates new one and opens the stream.
    auto retry_handler = [&](const boost::system::error_code &ec) {
        // check if the `failed_retry_count` exceeds the maximum amount of allowed retries.
        // NOTE: this can be changed to what ever policy, e.g. increase the `retry_duration` instead of exiting.
        if (failed_retry_count > 10) {
            // stop the stream obtainer loop.
            stop_stream_loop();
            // exit the `retry_handler`
            return;
        }
        BOOST_LOG_TRIVIAL(debug) << "`retry_handler` requesting lock on `cap_lock` mutex";
        lock_guard guard(cap_lock);
        // check if the stream is opened.
        if (cap->isOpened()) {
            BOOST_LOG_TRIVIAL(debug) << "video-capture is already opened.";
            // if so, close it.
            cap->release();
        }
        BOOST_LOG_TRIVIAL(debug) << "requesting a `VideoCapture`";
        // create a new capture.
        cap = create_capture();
        BOOST_LOG_TRIVIAL(debug) << "opening `VideoCapture` from `retry_handler`";
        // open the stream inside the retry handler.
        // this function blocks the while loop, because the loop is waiting for `cap_lock` mutex to be unlocked.
        bool open_result = cap->open(stream_url);

        // if opening a `VideoCapture` failed, then schedule another `retry_handler` to re-create a `VideoCapture`
        if (!open_result) {
            // increase the failed count.
            increase_failed_count();
            // schedule another `retry_handler`
            return schedule_retry_handler();
        }

        // reset the failed count, because the operation was successful.
        reset_failed_count();
    };

    boost::asio::io_service io;
    boost::asio::deadline_timer t(io, retry_duration);


    schedule_retry_handler = [&]() {
        // this sets the expiration time to the retry_duration, and cancels any awaiting tasks.
        t.expires_from_now(retry_duration);
        // this is acts like nodejs `setTimeout`, it sets a function to be executed based on the retry_duration.
        t.async_wait(retry_handler);
    };

    boost::asio::post(io, [&]() {
        while (is_stream_running) {
            lock_guard guard(cap_lock);
            // because the loop condition is not related to the `VideoCapture::isOpened`, it may be called on a closed capture.
            // since the loop is dependent on a `lock_guard`, it's not likely to be called on a closed capture when triggering the `retry_handler`
            if (!cap->isOpened()) continue;

            Mat frame;
            BOOST_LOG_TRIVIAL(trace) << "reading frame from VideoCapture";
            bool grabbed = cap->read(frame);

            if (grabbed) {
                BOOST_LOG_TRIVIAL(trace) << "pushing frame to frames _queue";
                queue->push(frame);
                // if the `if(grabbed)` condition is not met, then the function will execute, because a call to `t.expires_from_now` cancels any awaiting tasks.
                // this ensures that if the grabbed condition is met, the `retry_handler` is not triggered.
                schedule_retry_handler();
            }
        }
    });


    BOOST_LOG_TRIVIAL(debug) << "running io loop";

    // start the `io_service` loop.
    io.run();

    BOOST_LOG_TRIVIAL(debug) << "io loop ended";

    BOOST_LOG_TRIVIAL(debug) << "video capture is closed";
    BOOST_LOG_TRIVIAL(info) << "quitting stream subscriber";
}