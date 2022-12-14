cmake_minimum_required(VERSION 3.16)
project(stream_obtainer)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

set(
        impl_headers

        impl/tasks/subscribe_to_stream_task_impl/subscribe_to_stream_task_impl.h
        impl/tasks/publish_stream_task_impl/publish_stream_task_impl.h
)

add_library(
        stream_obtainer_lib
        stream_obtainer.cpp

        impl/frames_queue_impl.cpp

        impl/tasks/tasks.cpp
        impl/tasks/subscribe_to_stream_task_impl/subscribe_to_stream_task_impl.cpp
        impl/tasks/publish_stream_task_impl/publish_stream_task_impl.cpp

        ${impl_headers}
)

target_include_directories(
        stream_obtainer_lib
        PRIVATE
        interfaces
        ${OpenCV_INCLUDE_DIRS}
        PUBLIC
        include
)


add_executable(
        stream_obtainer_standalone
        main.cpp
)

target_link_libraries(stream_obtainer_standalone stream_obtainer_lib core)

install_project_binaries(stream_obtainer_standalone)

copy_local_file(stream_obtainer_standalone configs.local.json)