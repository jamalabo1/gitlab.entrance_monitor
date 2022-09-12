cmake_minimum_required(VERSION 3.16)
project(utils-tests)

set(CMAKE_CXX_STANDARD 17)

include(utils)

add_library(utils_tests vector_test.cpp)

create_testing_target(utils)