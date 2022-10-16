//
// Created by root on 10/5/22.
//

#include "match_to_shape.h"
#include <utils/vector.h>

namespace blocking_computation::utils {
    // since opencv has a free function called transform it cannot be used.
    namespace vector_utils = ::utils::vector;
    using std::vector;
    using cv::Point;
    using cv::Size;

    vector<Point> match_to_shape(vector<Point> &pts, Size original_shape, Size shape) {
        float w_factor = shape.width / float(original_shape.width);
        float h_factor = shape.height / float(original_shape.height);


        return vector_utils::transform<Point, Point>(pts, [w_factor, h_factor](Point &p) {
            return Point(p.x * w_factor, p.y * h_factor);
        });
    }
}
