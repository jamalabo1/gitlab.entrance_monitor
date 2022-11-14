//
// Created by jamal on 14/11/2022.
//
#include <utils/uuid.h>

#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

namespace utils::uuid {
    static auto uuid_generator = boost::uuids::random_generator();

    std::string generateId() {
        return to_string(uuid_generator());
    }
}