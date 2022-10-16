//
// Created by root on 9/29/22.
//
#include "frames_queue.h"


namespace stream_obtainer {
    using fruit::createComponent;

    FramesQueueComponent getFramesQueueComponent() {
        return createComponent()
                .registerProvider([]() {
                    return new FramesQueue();
                });
    }
}
