//
// Created by jamal on 26/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_MAT_H
#define ENTRANCE_MONITOR_V2_MAT_H

#include <vector>
#include <string>
#include <opencv2/core/mat.hpp>

//std::string mat_to_base64(const cv::Mat &img);
//cv::Mat base64_to_mat(const std::string& base64);
namespace utils::mat {
    std::vector<uint8_t> mat_to_encoded_vector(const cv::Mat &, const std::string & = "jpg");

    std::string mat_to_encoded_string(const cv::Mat &, const std::string & = "jpg");
};

#endif //ENTRANCE_MONITOR_V2_MAT_H
