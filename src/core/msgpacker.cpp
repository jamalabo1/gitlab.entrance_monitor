//
// Created by jamal on 13/09/2022.
//

#include <core/msgpacker.h>
#include <opencv2/imgcodecs.hpp>

namespace core::msgpacker {
    using cv::Mat;
    using std::string;
    using cv::IMREAD_COLOR;

    using views::FrameView;
//    using views::FrameView;

    Mat unpack_frame_mat(const string &body) {
        FrameView view = unpack_frame(body);
        return unpack_frame_mat(view);
    }

//    Mat unpack_frame_mat(const FrameView &view) {
//        return imdecode(view.frame_data, IMREAD_COLOR);
//    }

    Mat unpack_frame_mat(const FrameView &view) {
        return imdecode(string_to_vector(view.frame_data()), IMREAD_COLOR);
    }


    FrameView unpack_frame(const string &body) {
        auto view = core::msgpacker::pb::unpack<FrameView>(body);
        return view;
    }

}
