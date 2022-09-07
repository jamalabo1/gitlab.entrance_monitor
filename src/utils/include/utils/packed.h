//
// Created by jamal on 12/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_PACKED_H
#define ENTRANCE_MONITOR_V2_PACKED_H

#include <opencv2/core/mat.hpp>
#include <view_models/frame_view.h>

// returns a mat frame from jpeg encoded bytes FrameObject
FrameView unpack_frame(const std::string &);

cv::Mat unpack_frame_mat(const std::string &);
cv::Mat unpack_frame_mat(const FrameView &);

#endif //ENTRANCE_MONITOR_V2_PACKED_H
