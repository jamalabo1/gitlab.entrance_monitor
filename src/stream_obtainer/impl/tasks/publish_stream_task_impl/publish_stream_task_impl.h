//
// Created by root on 9/29/22.
//

#ifndef ENTRANCE_MONITOR_V2_STREAM_OBTAINER_TASKS_PUBLISH_STREAM_IMPL_H
#define ENTRANCE_MONITOR_V2_STREAM_OBTAINER_TASKS_PUBLISH_STREAM_IMPL_H

#include "tasks/publish_stream_task.h"

#include "frames_queue.h"
#include <core/communication/publish.h>

namespace stream_obtainer::tasks::impl {
    class PublishStreamTaskImpl : public PublishStreamTask {
    private:
        FramesQueue* queue_;
        core::communication::publish::PublisherFactory* publisher_factory_;
    public:

        INJECT(PublishStreamTaskImpl(FramesQueue*, core::communication::publish::PublisherFactory*));

        TaskResult operator()() override;
    };
}

#endif //ENTRANCE_MONITOR_V2_STREAM_OBTAINER_TASKS_PUBLISH_STREAM_IMPL_H
