//
// Created by root on 10/1/22.
//
#include "configurations_local_impl.h"

#include <filesystem>
#include <boost/property_tree/json_parser.hpp>

namespace fs = std::filesystem;

std::stringstream read_file(fs::path path) {
    std::ifstream f(path);

    std::stringstream ss;

    ss >> f.rdbuf();

    return ss;
//    const auto sz = fs::file_size(path);
//
//    std::string result(sz, '\0');
//
//    f.read(result.data(), sz);
//
//   return result;
}
core::impl::ConfigurationsLocalImpl::ConfigurationsLocalImpl() {
    auto ss = read_file("configs.json");

    boost::property_tree::read_json(ss, pt_);
}

std::string core::impl::ConfigurationsLocalImpl::get_value_from_key(const std::string &key) {
    return pt_.get<std::string>(key);
}

core::ConfigurationsComponent core::getConfigurationsComponent() {
    return fruit::createComponent()
        .bind<Configurations,impl::ConfigurationsLocalImpl>();
}