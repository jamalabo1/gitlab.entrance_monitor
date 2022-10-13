//
// Created by jamal on 13/08/2022.
//

#include <utils/reference_time.h>
#include <chrono>

namespace utils::reference_time {
    using namespace std::chrono;

    uint64_t getCurrentTimestamp() {

        system_clock::time_point tp = system_clock::now();
        system_clock::duration dtn = tp.time_since_epoch();

        uint64_t m = duration_cast<milliseconds>(dtn).count();

        return m;
    }
}
