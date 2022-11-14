//
// Created by jamal on 12/08/2022.
//
#include "utils/mat.h"
#include <utils/vector.h>

#include <opencv2/imgcodecs.hpp>

namespace utils::mat {
    using cv::Mat;
    using std::string;
    using vector::vector_to_string;
    using std::vector;

    vector<uint8_t> mat_to_encoded_vector(const Mat &mat, const string &ext) {
        vector<uint8_t> v;
        imencode("." + ext, mat, v);
        return v;
    }

    string mat_to_encoded_string(const Mat &mat, const string &ext) {
        return vector_to_string(mat_to_encoded_vector(mat, ext));
    }
}
