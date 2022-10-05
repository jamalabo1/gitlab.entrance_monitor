//
// Created by root on 10/1/22.
//
#include "configurations_local_impl.h"

#include <filesystem>
#include <boost/property_tree/json_parser.hpp>

namespace fs = std::filesystem;

core::impl::ConfigurationsLocalImpl::ConfigurationsLocalImpl() {
    boost::property_tree::read_json("configs.local.json", pt_);
}

std::string core::impl::ConfigurationsLocalImpl::get_value_from_key(const std::string &key) {
    return pt_.get<std::string>(key);
}

core::ConfigurationsComponent core::getConfigurationsComponent() {
    return fruit::createComponent()
        .bind<Configurations,impl::ConfigurationsLocalImpl>();
}