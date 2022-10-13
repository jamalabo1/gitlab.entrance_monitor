//
// Created by jamal on 29/09/2022.
//

#ifndef ENTRANCE_MONITOR_V2_STREAM_OBTAINER_IMPL_TASKS_SUBSCRIBE_TO_STREAM_TASK_H
#define ENTRANCE_MONITOR_V2_STREAM_OBTAINER_IMPL_TASKS_SUBSCRIBE_TO_STREAM_TASK_H

#include <core/retry.h>

#include "tasks/subscribe_to_stream_task.h"
#include <opencv2/videoio.hpp>

namespace stream_obtainer::tasks::impl {
    class SubscribeToStreamTaskImpl : public SubscribeToStreamTask {
    private:
        FramesQueue* queue_;
        unique_ptr<cv::VideoCapture> cap_;
        std::string stream_url_;
        unique_ptr<core::retry::RetryPolicy> retry_policy_;
        // capture lock, to ensure that `retry_handler` does not overwrite an in-use `capture`.
        std::mutex cap_lock;
    public:

        INJECT(SubscribeToStreamTaskImpl(core::Configurations*, FramesQueue*, core::retry::Factory));

        bool configure() override;

        TaskResult operator()() override;


       bool retry_handler();
       void retry_stop_handler();

    };
}

#endif //ENTRANCE_MONITOR_V2_STREAM_OBTAINER_IMPL_TASKS_SUBSCRIBE_TO_STREAM_TASK_H
