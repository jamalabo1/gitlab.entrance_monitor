//
// Created by jamal on 29/09/2022.
//

#include "subscribe_to_stream_task_impl.h"

using namespace std;
using namespace cv;
using namespace stream_obtainer::tasks;

unique_ptr<VideoCapture> create_capture() {
    BOOST_LOG_TRIVIAL(trace) << "creating `cv::VideoCapture`";
    return make_unique<VideoCapture>();
}

impl::SubscribeToStreamTaskImpl::SubscribeToStreamTaskImpl(core::Configurations* configs, FramesQueue* framesQueue, core::retry::Factory retry_policy_factory) {
    cap_ = create_capture();
    queue_ = framesQueue;
    stream_url_ = configs->get("camera-stream-url");
    retry_policy_ = retry_policy_factory(core::retry::RetryPolicy::Options{
        .retry_duration = boost::posix_time::seconds(30),
        .retry_handler = [this]() { return retry_handler(); },
        .fail_handler = [this] { retry_stop_handler(); }
    });
}

core::Task::TaskResult impl::SubscribeToStreamTaskImpl::operator()() {

    BOOST_LOG_TRIVIAL(debug) << "subscribing to stream";

    BOOST_LOG_TRIVIAL(trace) << "opening `VideoCapture` stream";
    cap_->open(stream_url_);

    BOOST_LOG_TRIVIAL(trace) << "posting work";

    while (token_->isActive()) {

        // NOTE: problem with locking is blocking time.
        // TODO: re-implement to use lock-free approach.
        cap_lock.lock();

        // because the loop condition is not related to the `VideoCapture::isOpened`, it may be called on a closed capture.
        // since the loop is dependent on a `lock_guard`, it's not likely to be called on a closed capture when triggering the `retry_handler`
        // so it's just a safeguard.
        if (!cap_->isOpened()) {
            cap_lock.unlock();
            continue;
        }

        Mat frame;
        BOOST_LOG_TRIVIAL(trace) << "reading frame from VideoCapture";
        bool grabbed = cap_->read(frame);
        cap_lock.unlock();


        if (grabbed) {
            BOOST_LOG_TRIVIAL(trace) << "pushing frame to frames _queue";
            queue_->push(frame);
            // if the `if(grabbed)` condition is not met, then the function will execute, because a call to `t.expires_from_now` cancels any awaiting tasks.
            // this ensures that if the grabbed condition is met, the `retry_handler` is not triggered.
            retry_policy_->ping();
        }
    }
}

bool impl::SubscribeToStreamTaskImpl::retry_handler() {
    BOOST_LOG_TRIVIAL(debug) << "[SubscribeToStreamTaskImpl::retry_handler] retrying to ensure video stream is opened.";

    BOOST_LOG_TRIVIAL(trace) << "`retry_handler` requesting lock on `cap_lock` mutex";
    lock_guard guard(cap_lock);
    // check if the stream is opened.
    if (cap_->isOpened()) {
        BOOST_LOG_TRIVIAL(debug) << "video-capture is already opened.";
        // since the ping policy was not met, it means there is a problem with the video stream even if it's opened or not,
        cap_->release();
    }
    BOOST_LOG_TRIVIAL(trace) << "requesting a `VideoCapture`";
    // create a new capture.
    cap_ = create_capture();
    BOOST_LOG_TRIVIAL(debug) << "opening `VideoCapture` from `retry_handler`";
    // open the stream inside the retry handler.
    // this function blocks the while loop, because the loop is waiting for `cap_lock` mutex to be unlocked.
    return cap->open(stream_url_);
}

void impl::SubscribeToStreamTaskImpl::retry_stop_handler() {
    BOOST_LOG_TRIVIAL(trace) << "calling the stream token to be canceled.";
    // stop the stream obtaining loop
    token_->cancel();
}


