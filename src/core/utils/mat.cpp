//
// Created by jamal on 12/08/2022.
//
#include "utils/mat.h"

#include <opencv2/imgcodecs.hpp>

using namespace std;
using cv::Mat;

vector<uint8_t> utils::mat::mat_to_encoded_vector( const Mat &mat, const string &ext) {
    vector<uint8_t> v;
    imencode("." + ext, mat, v);
    return v;
}
