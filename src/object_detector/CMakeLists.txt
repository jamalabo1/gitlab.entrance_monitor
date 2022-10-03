cmake_minimum_required(VERSION 3.16)
project(object_detector)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)

set(private_headers

        impl/object_detector_impl.h
        impl/frame_message_handler.h
        interfaces/detection_result.h
        interfaces/detector.h
        impl/download_file.h
        utils/is_cuda_available.h interfaces/tasks/detect_objects_in_stream_task.h interfaces/tasks.h)

add_library(
        object_detector_lib
        object_detector.cpp
        impl/object_detector_impl.cpp
        impl/frame_message_handler.cpp
        impl/download_file.cpp
        ${private_headers}
        utils/is_cuda_available.cpp impl/tasks/tasks.cpp impl/tasks/detect_objects_in_stream_task_impl/detect_objects_in_stream_impl.cpp impl/tasks/detect_objects_in_stream_task_impl/detect_objects_in_stream_impl.h)

target_include_directories(
        object_detector_lib
        PRIVATE
        ${OpenCV_INCLUDE_DIRS}
        ${CURL_INCLUDE_DIR}
        impl
        utils
        interfaces
        PUBLIC
        include
)

target_link_libraries(
        object_detector_lib
        PRIVATE
        ${CURL_LIBRARIES}
        PUBLIC
        core
)

#add_custom_command(
#        TARGET object_detector_lib POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        "${PROJECT_SOURCE_DIR}/assets"
#        $<TARGET_FILE_DIR:object_detector_lib>
#)


add_executable(
        object_detector_standalone
        main.cpp
)

target_link_libraries(
        object_detector_standalone
        object_detector_lib
)

install_project_binaries(object_detector_standalone)