//
// Created by root on 9/29/22.
//
#include "frames_queue.h"

using fruit::createComponent;
using stream_obtainer::FramesQueueComponent;

FramesQueueComponent stream_obtainer::getFramesQueueComponent() {
    return createComponent()
    .registerProvider([]() {
        return new FramesQueue();
    });
}
