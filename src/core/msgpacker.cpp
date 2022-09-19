//
// Created by jamal on 13/09/2022.
//

#include <core/msgpacker.h>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;
using namespace core::msgpacker;


Mat core::msgpacker::unpack_frame_mat(const string &body) {
    FrameView view = unpack_frame(body);
    return unpack_frame_mat(view);
}

Mat core::msgpacker::unpack_frame_mat(const FrameView& view) {
    return imdecode(view.frame_data, IMREAD_COLOR);
}

FrameView core::msgpacker::unpack_frame(const string &body) {
    auto view = core::msgpacker::unpack<FrameView>(body);
    return view;
}
