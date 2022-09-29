//
// Created by root on 9/28/22.
//

#ifndef ENTRANCE_MONITOR_V2_FRAMES_QUEUE_H
#define ENTRANCE_MONITOR_V2_FRAMES_QUEUE_H

#include <opencv2/core/mat.hpp>
#include <core/queue_fps.h>

namespace stream_obtainer {
    using FramesQueue = core::QueueFPS<cv::Mat>;
}

#endif //ENTRANCE_MONITOR_V2_FRAMES_QUEUE_H
