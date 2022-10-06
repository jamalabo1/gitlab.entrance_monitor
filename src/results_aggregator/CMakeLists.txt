cmake_minimum_required(VERSION 3.16)
project(result_aggregator)

set(CMAKE_CXX_STANDARD 17)


set(private_headers
        impl/aggregator_impl.h

        impl/tasks/aggregate_blocking_results_task_impl/aggregate_blocking_results_task_impl.h
        impl/tasks/publish_aggregate_results_task_impl/publish_aggregate_results_task_impl.h
        )

add_library(
        results_aggregator_lib
        results_aggregator.cpp
        impl/aggregator_impl.cpp

        impl/tasks/tasks.cpp
        impl/tasks/aggregate_blocking_results_task_impl/aggregate_blocking_results_task_impl.cpp
        impl/tasks/publish_aggregate_results_task_impl/publish_aggregate_results_task_impl.cpp

        ${private_headers}
)


target_include_directories(
        results_aggregator_lib
        PRIVATE
        impl
        interfaces
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

copy_required_file(results_aggregator_standalone configs.local.json)
