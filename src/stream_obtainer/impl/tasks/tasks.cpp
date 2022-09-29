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
    .registerProvider([]() {
        return std::vector<core::Task*>();
    })
    .install(getFramesQueueComponent)
    .install(getStreamObtainerPublishStreamTask)
    .install(getStreamObtainerSubscribeToStreamTask);
}