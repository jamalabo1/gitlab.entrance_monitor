//
// Created by root on 10/5/22.
//

#ifndef ENTRANCE_MONITOR_V2_COMPARE_CONTOURS_AREA_H
#define ENTRANCE_MONITOR_V2_COMPARE_CONTOURS_AREA_H

#include <vector>
#include <opencv2/core/types.hpp>

namespace blocking_computation::utils {
    bool compareContoursArea(const std::vector<cv::Point> &, const std::vector<cv::Point> &);
}

#endif //ENTRANCE_MONITOR_V2_COMPARE_CONTOURS_AREA_H
