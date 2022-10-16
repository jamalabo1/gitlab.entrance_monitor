//
// Created by jamal on 08/09/2022.
//
#include <opencv2/cudaarithm.hpp>

#include "is_cuda_available.h"

namespace object_detector::utils {
    // checks if cuda is available on running host.
    bool is_cuda_available() noexcept {
        // simple check, but is good enough?!
        return cv::cuda::getCudaEnabledDeviceCount() > 0;
    }
}
