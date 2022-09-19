//
// Created by jamal on 02/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_STREAM_SUBSCRIBER_H
#define ENTRANCE_MONITOR_V2_STREAM_SUBSCRIBER_H

#include <opencv2/core/mat.hpp>
#include <core/queue_fps.h>
#include <core/ptrs.h>


typedef core::QueueFPS<cv::Mat> FramesQueue;

void subscribe_to_stream(const std::string &stream_url, shared_ptr<FramesQueue>& queue);

#endif //ENTRANCE_MONITOR_V2_STREAM_SUBSCRIBER_H
