cmake_minimum_required(VERSION 3.16)
project(blocking_computation)

set(CMAKE_CXX_STANDARD 17)


find_package(OpenCV REQUIRED)

set(private_headers

        impl/tasks/compute_blockage_task_impl/compute_blockage_task_impl.h

        utils/match_to_shape.h
        utils/compare_contours_area.h
        utils/compute_intersection.h

        )

add_library(
        blocking_computation_lib
        blocking_computation.cpp

        impl/tasks/tasks.cpp
        impl/tasks/compute_blockage_task_impl/compute_blockage_task_impl.cpp

        utils/match_to_shape.cpp
        utils/compare_contours_area.cpp
        utils/compute_intersection.cpp

        ${private_headers}
)


target_include_directories(
        blocking_computation_lib
        PRIVATE
        ${OpenCV_INCLUDE_DIRS}
        interfaces
        utils
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