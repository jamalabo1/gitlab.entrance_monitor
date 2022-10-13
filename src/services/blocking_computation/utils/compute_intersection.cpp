//
// Created by root on 10/5/22.
//

#include "compute_intersection.h"

#include <core/msgpacker.h>

#include <opencv2/imgproc.hpp>

#include "compare_contours_area.h"

namespace blocking_computation::utils {
    using std::vector;
    using cv::Mat;
    using cv::Size;
    using cv::Point;
    using cv::Rect;
    using cv::COLOR_BGR2GRAY;
    using cv::THRESH_BINARY;
    using cv::THRESH_OTSU;
    using cv::RETR_LIST;
    using cv::CHAIN_APPROX_SIMPLE;

    using views::DetectionResultObjectView;

    using std::ref;
    using core::msgpacker::unpack_frame_mat;
    using cv::GaussianBlur;
    using utils::compareContoursArea;

    boost::optional<bool>
    compute_intersection(const DetectionResultObjectView &detection_result_object,
                         Size &frameDimension, vector<Point> &boundingPoints) {
        static auto kernel_size = Size(3, 3);

        if (detection_result_object.confidence < 80) return {};

        Mat object = unpack_frame_mat(detection_result_object.object);


        Mat gray;
        cvtColor(object, gray, COLOR_BGR2GRAY);

        Mat object_mask = Mat::zeros(frameDimension, CV_8UC1);

        Rect roi(cv::Point(detection_result_object.box[0], detection_result_object.box[1]), gray.size());
        gray.copyTo(object_mask(roi));


        Mat blurred;
        GaussianBlur(object_mask, blurred, ref(kernel_size), 0);

        Mat thresh;
        threshold(
                blurred,
                thresh,
                0,
                255,
                THRESH_BINARY | THRESH_OTSU
        );

        std::vector<std::vector<cv::Point> > contours;

        findContours(thresh, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
        if (contours.empty()) return {};
        std::sort(contours.begin(), contours.end(), compareContoursArea);

        // take the largest contour only
        contours.resize(1);
//    contours.emplace_back(
//            boundingPoints
//    );

        Mat mask_1 = Mat::zeros(frameDimension, CV_8UC1);
        Mat mask_2 = Mat::zeros(frameDimension, CV_8UC1);

        drawContours(
                mask_1,
                contours,
                0,
                255
        );
        fillPoly(
                mask_2,
                boundingPoints,
                255
        );


        Mat intersection_mask;

        bitwise_and(mask_1, mask_2, intersection_mask);

        int intersection_sum = countNonZero(intersection_mask);
        return intersection_sum > 10;
    }

}
