//
// Created by root on 10/5/22.
//

#ifndef ENTRANCE_MONITOR_V2_COMPUTE_INTERSECTION_H
#define ENTRANCE_MONITOR_V2_COMPUTE_INTERSECTION_H

#include <vector>
#include <boost/optional.hpp>
#include <opencv2/core/types.hpp>
#include <view_models/detection_result_view.pb.h>

namespace blocking_computation::utils {
    boost::optional<bool>
    compute_intersection(const views::DetectionResultObjectView &detection_result_object,
                         cv::Size &frameDimension,
                         std::vector<cv::Point> &boundingPoints
    );
}

#endif //ENTRANCE_MONITOR_V2_COMPUTE_INTERSECTION_H
