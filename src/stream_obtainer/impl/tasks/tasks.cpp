//
// Created by root on 9/29/22.
//
#include "tasks.h"

using fruit::createComponent;
using stream_obtainer::tasks::getStreamObtainerPublishStreamTask;
using stream_obtainer::tasks::getStreamObtainerSubscribeToStreamTask;

using stream_obtainer::tasks::Components;

Components stream_obtainer::tasks::getStreamObtainerTasks() {
    return createComponent()
    .registerProvider(MAKE_TASKS_PROVIDER(tasks::PublishStreamTask, tasks::SubscribeToStreamTask))
    .install(getFramesQueueComponent)
    .install(getStreamObtainerPublishStreamTask)
    .install(getStreamObtainerSubscribeToStreamTask);
}