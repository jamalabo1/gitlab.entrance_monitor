cmake_minimum_required(VERSION 3.16)
project(entrance_monitor_v2)

set(CMAKE_CXX_STANDARD 17)

set(mock_headers
        mock/azure_secret_client_mock.h
        )

add_library(core_tests
        cancellation_token_test.cpp
        queue_fps_test.cpp

        utils/vector_test.cpp

        impl/configurations_impl_test.cpp
        )

target_include_directories(core_tests PRIVATE mock)

create_testing_target(core)