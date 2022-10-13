//
// Created by root on 10/2/22.
//

#ifndef ENTRANCE_MONITOR_V2_TASKS_DETECT_OBJECTS_IN_STREAM_TASK_IMPL_H
#define ENTRANCE_MONITOR_V2_TASKS_DETECT_OBJECTS_IN_STREAM_TASK_IMPL_H

#include "tasks/detect_objects_in_stream_task.h"

#include <core/communication.h>

#include "detector.h"

namespace object_detector::tasks::detect_objects_in_stream::impl {

    class DetectObjectsInStreamTaskImpl :
            public DetectObjectsInStreamTask,
            public core::communication::consume::ConsumerMessageHandler,
            public std::enable_shared_from_this<DetectObjectsInStreamTaskImpl> {
    private:
        shared_ptr<core::communication::consume::Consumer> consumer_;
        unique_ptr<core::communication::consume::ConsumeOptions> consume_options_;

        shared_ptr<core::communication::publish::PublisherFactory> publisher_factory_;
        shared_ptr<core::communication::publish::Publisher> publisher_;

        shared_ptr<object_detector::Detector> detector_;

    public:
        INJECT(DetectObjectsInStreamTaskImpl(
                 shared_ptr<object_detector::Detector>,
                 shared_ptr<core::communication::consume::Consumer>,
                 shared_ptr<core::communication::publish::PublisherFactory>
        ));

        RunOptions setup(shared_ptr<core::IoContext> ptr, shared_ptr<core::CancellationToken> sharedPtr) override;

        bool configure() override;

        TaskResult operator()() override;

        void operator()(const core::communication::consume::ConsumerMessage::ptr_t &envelope) const override;
    };
}

#endif //ENTRANCE_MONITOR_V2_TASKS_DETECT_OBJECTS_IN_STREAM_TASK_IMPL_H
