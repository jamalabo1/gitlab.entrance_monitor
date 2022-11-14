//
// Created by jamal on 13/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_VECTOR_H
#define ENTRANCE_MONITOR_V2_VECTOR_H

#include <vector>
#include <functional>
#include <algorithm>

namespace utils::vector {

    template<typename BaseType, typename ExpectedType>
    std::vector<ExpectedType> transform(std::vector<BaseType> v1, std::function<ExpectedType(BaseType &)> func) {

        std::vector<ExpectedType> nextVector(v1.size());

        std::transform(
                v1.begin(),
                v1.end(),
                nextVector.begin(),
                func
        );

        return nextVector;
    }

    template<typename BaseType>
    inline std::string vector_to_string(const std::vector<BaseType> &data) {
        return std::string(data.begin(), data.end());
    }
}

#endif //ENTRANCE_MONITOR_V2_VECTOR_H
