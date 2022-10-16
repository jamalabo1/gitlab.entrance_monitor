cmake_minimum_required(VERSION 3.16)
project(models)

add_library(view_models INTERFACE)

target_include_directories(view_models INTERFACE include)