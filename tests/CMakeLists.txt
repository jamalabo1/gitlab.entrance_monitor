# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.
cmake_minimum_required(VERSION 3.16)
project(tests)

set(CMAKE_CXX_STANDARD 17)

include(utils)

create_global_testing_target(entrance_monitor_tests main.cpp) # create a global target for sub-tests to link their test library to

add_subdirectory(core)

enable_global_testing_target() # enable this target by linking the global target to an executable (order is important, for the global test target to populate it's self)