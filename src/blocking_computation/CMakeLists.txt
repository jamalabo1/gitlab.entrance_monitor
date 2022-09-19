cmake_minimum_required(VERSION 3.16)
project(blocking_computation)

set(CMAKE_CXX_STANDARD 17)


find_package(OpenCV REQUIRED)

set(private_headers

        impl/detection_message_handler.h
        )

add_library(
        blocking_computation_lib
        blocking_computation.cpp

        impl/detection_message_handler.cpp
)


target_include_directories(
        blocking_computation_lib
        PRIVATE
        ${OpenCV_INCLUDE_DIRS}
        impl
        PUBLIC
        include
)

add_executable(
        blocking_computation_standalone
        main.cpp
)


target_link_libraries(
        blocking_computation_standalone
        blocking_computation_lib
)

install_project_binaries(blocking_computation_standalone)