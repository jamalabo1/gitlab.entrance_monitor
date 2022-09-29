//
// Created by root on 9/28/22.
//

#ifndef ENTRANCE_MONITOR_V2_FRAMES_QUEUE_H
#define ENTRANCE_MONITOR_V2_FRAMES_QUEUE_H

#include <core/init.h>

#include <core/queue_fps.h>

#include <opencv2/core/mat.hpp>

namespace stream_obtainer {
    using FramesQueue = core::QueueFPS<cv::Mat>;

    using $FramesQueue = $Exported<FramesQueue>;
    using FramesQueueComponent = $FramesQueue::PureComponent;

    FramesQueueComponent getFramesQueueComponent();
}

#endif //ENTRANCE_MONITOR_V2_FRAMES_QUEUE_H
