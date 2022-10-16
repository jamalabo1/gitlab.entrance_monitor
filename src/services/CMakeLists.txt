cmake_minimum_required(VERSION 3.16)
project(services)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(blocking_computation)
add_subdirectory(object_detector)
add_subdirectory(results_aggregator)
add_subdirectory(stream_obtainer)
add_subdirectory(audio_controller)