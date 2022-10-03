//
// Created by jamal on 28/05/2022.
//

#include "stream_obtainer/stream_obtainer.h"

#include <core/logging.h>

#include "tasks.h"

using fruit::createComponent;
using stream_obtainer::tasks::getStreamObtainerTasks;
using core::getCoreComponents;
using core::Service;


stream_obtainer::StreamObtainer::StreamObtainer(const std::vector<shared_ptr<core::Task>> &tasks) {
    registerTasks(tasks);
}

int stream_obtainer::StreamObtainer::setup() {
    // no setup is required for stream obtainer.
    return 0;
}

stream_obtainer::StreamObtainer::~StreamObtainer() = default;


stream_obtainer::StreamObtainerComponent stream_obtainer::getStreamObtainerComponent() {
    return createComponent()
            .install(getStreamObtainerTasks)
            .install(getCoreComponents)
            .addMultibinding<Service, StreamObtainer>();
}