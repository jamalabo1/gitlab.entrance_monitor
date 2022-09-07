cmake_minimum_required(VERSION 3.16)
project(apps)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        project_runner
        main.cpp
)

target_link_directories(
        project_runner
        PUBLIC
        core
)

#add_custom_command(
#        TARGET project_runner POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        "${PROJECT_SOURCE_DIR}/assets"
#        $<TARGET_FILE_DIR:project_runner>
#)

target_link_libraries(
        project_runner
        PRIVATE
        stream_obtainer_lib
        object_detector_lib
        blocking_computation_lib
        results_aggregator_lib
        PUBLIC
        core
)