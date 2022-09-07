cmake_minimum_required(VERSION 3.16)
project(stream_obtainer)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)


add_library(
        stream_obtainer_lib
        stream_obtainer.cpp
        stream_subscriber.cpp
)

target_include_directories(
        stream_obtainer_lib
        PRIVATE
        ${OpenCV_INCLUDE_DIRS}
        PUBLIC
        include

)


target_link_libraries(
        stream_obtainer_lib
        PRIVATE
        ${OpenCV_LIBS}
)


add_executable(stream_obtainer_standalone main.cpp)

target_link_libraries(stream_obtainer_standalone stream_obtainer_lib core)


install_project_binaries(stream_obtainer_standalone)
expose_target(stream_obtainer stream-obtainer)