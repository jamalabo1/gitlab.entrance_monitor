//
// Created by jamal on 12/08/2022.
//
#include <core/msgpacker.h>

#include "utils/packed.h"

#include <core/string_utils.h>

#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

Mat unpack_frame_mat(const string &body) {
    FrameView view = unpack_frame(body);
    return unpack_frame_mat(view);
}

Mat unpack_frame_mat(const FrameView& view) {
    return imdecode(view.frame_data, IMREAD_COLOR);
}

FrameView unpack_frame(const string &body) {
    auto view = core::msgpacker::unpack<FrameView>(body);
    return view;
}

