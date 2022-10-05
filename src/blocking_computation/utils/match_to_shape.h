//
// Created by root on 10/5/22.
//

#ifndef ENTRANCE_MONITOR_V2_MATCH_TO_SHAPE_H
#define ENTRANCE_MONITOR_V2_MATCH_TO_SHAPE_H

#include <vector>
#include <opencv2/core/types.hpp>

namespace blocking_computation::utils {
    std::vector<cv::Point> match_to_shape(std::vector<cv::Point> &pts, cv::Size original_shape, cv::Size shape);
}

#endif //ENTRANCE_MONITOR_V2_MATCH_TO_SHAPE_H
