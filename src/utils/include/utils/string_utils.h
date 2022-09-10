//
// Created by jamal on 12/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_UTILS_STRING_UTILS_H
#define ENTRANCE_MONITOR_V2_UTILS_STRING_UTILS_H

#include <vector>
#include <string>

inline std::vector<uint8_t> string_to_vector(const std::string &str) {
    std::vector<uint8_t> v(str.begin(), str.end());
    return v;
}

#endif //ENTRANCE_MONITOR_V2_UTILS_STRING_UTILS_H
