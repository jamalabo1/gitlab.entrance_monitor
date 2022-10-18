//
// Created by jamal on 16/10/2022.
//

#ifndef ENTRANCE_MONITOR_V2_TYPES_H
#define ENTRANCE_MONITOR_V2_TYPES_H

#include <string>
#include <boost/type_index.hpp>

namespace utils {
    template <class T>
    std::string type_name(T) {
        return boost::typeindex::type_id<T>().pretty_name();
    }
}

#endif //ENTRANCE_MONITOR_V2_TYPES_H
