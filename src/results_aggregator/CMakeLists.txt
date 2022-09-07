cmake_minimum_required(VERSION 3.16)
project(result_aggregator)

set(CMAKE_CXX_STANDARD 17)


set(private_headers

        impl/aggregator_impl.h
        impl/blocking_result_message_handler.h
        )

add_library(
        results_aggregator_lib
        results_aggregator.cpp
        impl/blocking_result_message_handler.cpp
        impl/aggregator_impl.cpp
        ${private_headers}
)


target_include_directories(
        results_aggregator_lib
        PRIVATE
        impl
        PUBLIC
        include
)

add_executable(
        results_aggregator_standalone
        main.cpp
)


target_link_libraries(
        results_aggregator_standalone
        results_aggregator_lib
)

install_project_binaries(results_aggregator_standalone)