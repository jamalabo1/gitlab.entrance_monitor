cmake_minimum_required(VERSION 3.16)
project(object_detector)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)

set(private_headers

        impl/object_detector_impl.h
        impl/tasks/detect_objects_in_stream_task_impl/detect_objects_in_stream_impl.h

        utils/download_file.h
        utils/is_cuda_available.h
        )

add_library(
        object_detector_lib
        object_detector.cpp

        impl/tasks/tasks.cpp
        impl/tasks/detect_objects_in_stream_task_impl/detect_objects_in_stream_impl.cpp
        impl/object_detector_impl.cpp

        utils/download_file.cpp
        utils/is_cuda_available.cpp

        ${private_headers}
)

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

add_executable(
        object_detector_standalone
        main.cpp
)

target_link_libraries(
        object_detector_standalone
        object_detector_lib
)

install_project_binaries(object_detector_standalone)

if(PROJECT_IS_LOCAL)
    copy_required_file(object_detector_standalone configs.local.json)
ENDIF()