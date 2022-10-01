//
// Created by root on 10/1/22.
//

#ifndef ENTRANCE_MONITOR_V2_CONFIGURATIONS_LOCAL_IMPL_H
#define ENTRANCE_MONITOR_V2_CONFIGURATIONS_LOCAL_IMPL_H


#include <core/configurations.h>
#include <boost/property_tree/ptree.hpp>

namespace core::impl {

    class ConfigurationsLocalImpl : public Configurations {

    private:
        boost::property_tree::ptree pt_;


    protected:

        std::string get_value_from_key(const std::string &key) override;

    public:
        INJECT(ConfigurationsLocalImpl());

    };

}


#endif //ENTRANCE_MONITOR_V2_CONFIGURATIONS_LOCAL_IMPL_H
