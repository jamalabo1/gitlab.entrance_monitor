//
// Created by root on 9/29/22.
//
#include "tasks.h"

namespace stream_obtainer::tasks {

    Components getStreamObtainerTasks() {
        return CORE_TASKS_CREATE_COMPONENT(StreamObtainer, PublishStreamTask, SubscribeToStreamTask)
                .install(getFramesQueueComponent);
    }

}
