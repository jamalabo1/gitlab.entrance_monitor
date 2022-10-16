//
// Created by root on 10/1/22.
//
#include "configurations_local_impl.h"

#include <filesystem>
#include <boost/property_tree/json_parser.hpp>

namespace core {

    namespace impl {
        using std::string;
        using boost::property_tree::read_json;

        ConfigurationsLocalImpl::ConfigurationsLocalImpl() {
            read_json("configs.local.json", pt_);
        }

        string ConfigurationsLocalImpl::get_value_from_key(const string &key) {
            return pt_.get<string>(key);
        }
    }

    ConfigurationsComponent getConfigurationsComponent() {
        return fruit::createComponent()
                .bind<Configurations, impl::ConfigurationsLocalImpl>();
    }
}
