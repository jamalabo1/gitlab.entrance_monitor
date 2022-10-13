//
// Created by jamal on 28/05/2022.
//

#include "stream_obtainer/stream_obtainer.h"

#include <core/logging.h>

#include "tasks.h"


namespace stream_obtainer {

    using fruit::createComponent;
    using core::getCoreComponents;
    using core::Service;

    using tasks::getStreamObtainerTasks;

    StreamObtainer::StreamObtainer(const std::vector<shared_ptr<core::Task>> &tasks) {
        registerTasks(tasks);
    }

    StreamObtainer::~StreamObtainer() = default;

    StreamObtainerComponent getStreamObtainerComponent() {
        return createComponent()
                .install(getStreamObtainerTasks)
                .install(getCoreComponents)
                .addMultibinding<Service, StreamObtainer>();
    }
}
