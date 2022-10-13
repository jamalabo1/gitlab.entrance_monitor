//
// Created by root on 10/5/22.
//

#include "compare_contours_area.h"

#include <opencv2/imgproc.hpp>

namespace blocking_computation::utils {
    using std::vector;
    using cv::contourArea;
    using cv::Point;

bool compareContoursArea(const vector<Point> &c1, const vector<Point> &c2) {
    double a = fabs(contourArea(c1));
    double b = fabs(contourArea(c2));
    return (a > b);
}

}
