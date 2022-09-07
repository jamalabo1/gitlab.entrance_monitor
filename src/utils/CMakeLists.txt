cmake_minimum_required(VERSION 3.16)
project(utils)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)


add_library(
        utils
        packed.cpp
        mat.cpp time.cpp)


target_include_directories(
        utils
        PRIVATE
        include/utils
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
        include
)


target_link_libraries(
        core
        PRIVATE
        ${OpenCV_LIBS}
)
