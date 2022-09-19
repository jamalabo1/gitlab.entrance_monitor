cmake_minimum_required(VERSION 3.16)
project(entrance_monitor_v2)

# Add tasks subprojects
include(utils)

set(CMAKE_CXX_STANDARD 17)

add_library(core_tests "test.cpp" cancellation_token_test.cpp queue_fps_test.cpp)

create_testing_target(core)