//
// Created by jamal on 12/08/2022.
//
#include "utils/mat.h"

#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

vector<uint8_t> mat_to_encoded_vector( const cv::Mat &mat, const string &ext) {
    vector<uint8_t> v;
    imencode("." + ext, mat, v);
    return v;
}