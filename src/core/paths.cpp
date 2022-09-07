//
// Created by jamal on 17/08/2022.
//
#include <filesystem>
#include <core/paths.h>

std::string resolve_relative_path(const std::string &path) {
    auto apath = std::filesystem::absolute(path);
    return apath.string();
}