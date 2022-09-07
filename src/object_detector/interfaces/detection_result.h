//
// Created by jamal on 10/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_DETECTION_RESULT_H
#define ENTRANCE_MONITOR_V2_DETECTION_RESULT_H

#include <utility>
#include <vector>
#include <opencv2/core.hpp>

class DetectionResult {
public:

    std::vector<cv::Rect> boxes;
    std::vector<int> ids;
    std::vector<float> confidences;

    DetectionResult(std::vector<int> ids, std::vector<cv::Rect> boxes,
                    std::vector<float> confidences) : ids(std::move(ids)),
                                                      boxes(std::move(boxes)),
                                                      confidences(std::move(confidences)) {}

};

#endif //ENTRANCE_MONITOR_V2_DETECTION_RESULT_H
