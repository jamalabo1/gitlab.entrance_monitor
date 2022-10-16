//
// Created by jamal on 16/10/2022.
//
#include <utils/worker.h>
#include <cmath>
#include <thread>

namespace utils::worker {
    unsigned int get_cores() {
        auto hc = std::thread::hardware_concurrency();
        unsigned int constexpr v = 1;

        return std::max(hc, v);
    }
}