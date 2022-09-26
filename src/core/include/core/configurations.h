//
// Created by jamal on 02/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CONFIGURATIONS_H
#define ENTRANCE_MONITOR_V2_CONFIGURATIONS_H

#include <fruit/fruit.h>
#include <core/ptrs.h>
#include <string>
#include <sstream>

#include <utility>

namespace core {

    class Configurations {

    protected:
        virtual std::string get_value_from_key(const std::string &key) = 0;

    public:

        template<typename T = std::string>
        T get(const std::string &key) {
            std::string str_value = get_value_from_key(key);

            T val;

            std::istringstream ss(str_value);
            ss >> val;

            return val;
        }

        template<typename T>
        T operator[](const std::string &key) {
            return get<T>(key);
        }

    };

    using ConfigurationsComponent = fruit::Component<Configurations>;
    ConfigurationsComponent getConfigurationsComponent();
}

#endif //ENTRANCE_MONITOR_V2_CONFIGURATIONS_H
