cmake_minimum_required(VERSION 3.16)
project(core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Msgpack REQUIRED)
find_package(OpenCV REQUIRED)
# to fix issue of OpenCV_LIBS including libraries that are not built.
set(OpenCV_LIBS "opencv_core;opencv_dnn;opencv_highgui;opencv_imgcodecs;opencv_imgproc;opencv_ml;opencv_photo;opencv_video;opencv_videoio;opencv_bioinspired;opencv_cudaarithm;opencv_cudabgsegm;opencv_cudacodec;opencv_cudafilters;opencv_cudaimgproc;opencv_cudalegacy;opencv_cudawarping;opencv_cudev;opencv_dnn_objdetect;opencv_dnn_superres;opencv_fuzzy;opencv_hfs;opencv_img_hash;opencv_intensity_transform;opencv_line_descriptor;opencv_phase_unwrapping;opencv_plot;opencv_quality;opencv_reg;opencv_tracking;opencv_xphoto")
find_package(protobuf REQUIRED)

find_package(amqpcpp REQUIRED)
find_package(azure-identity-cpp CONFIG REQUIRED)
find_package(azure-security-keyvault-secrets-cpp CONFIG REQUIRED)

SET(impl_headers
        impl/amqp.h
        impl/amqp/channel_holder_impl.h
        impl/amqp/amqp_io_context_impl.h
        impl/amqp/amqp_connection_impl.h

        impl/communication/consume/consumer_impl.h
        impl/communication/consume/consumer_message.h

        impl/communication/publish/publisher_impl.h
        impl/communication/publish/publisher_factory.h


        impl/io_context_impl.h
        impl/gui_handler_impl.h

        impl/retry/retry_policy_impl.h
        )

set(configurations_srcs
        impl/configurations/configurations_local_impl.h
        impl/configurations/configurations_local_impl.cpp
        )

if (CORE_USE_AZURE_KEYVAULT)
    message(STATUS "Using azure key-vault as configuration implementation")
    set(configurations_srcs
            impl/configurations/configurations_azure_impl.h
            impl/configurations/configurations_azure_impl.cpp
            )
endif ()

add_library(
        core
        ${configurations_srcs}

        core.cpp
        standalone.cpp
        service.cpp
        task.cpp
        msgpacker.cpp

        utils/mat.cpp
        utils/time.cpp
        utils/worker.cpp
        utils/uuid.cpp

        impl/communication/publish/publisher.cpp
        impl/communication/publish/publisher_factory.cpp
        impl/communication/publish/publisher_impl.cpp

        impl/communication/consume/consumer_impl.cpp
        impl/communication/consume/consumer_message.cpp
        impl/communication/consume/consumer_message_handler.cpp

        impl/communication/communication.cpp
        impl/communication/consume/consume.cpp
        impl/communication/publish/publish.cpp

        impl/amqp/amqp.cpp
        impl/amqp/channel_holder_impl.cpp
        impl/amqp/amqp_io_context_impl.cpp
        impl/amqp/amqp_connection_impl.cpp

        impl/retry/retry.cpp
        impl/retry/retry_policy_impl.cpp

        impl/gui_handler_impl.cpp
        impl/io_context_impl.cpp

        ${impl_headers}
)

set_private_testable_include(
        ${CMAKE_CURRENT_LIST_DIR}/impl
        ${CMAKE_CURRENT_LIST_DIR}/interfaces
)


target_include_directories(
        core
        PRIVATE

        $<TARGET_PROPERTY:amqpcpp,INTERFACE_INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:core,private_include_directories>
        interfaces

        PUBLIC
        ${Msgpack_INCLUDE_DIR}
        ${FRUIT_INCLUDE_DIR}
        ${Boost_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries(
        core
        PRIVATE
        Azure::azure-identity
        Azure::azure-security-keyvault-secrets
        ${OpenCV_LIBS}
        protobuf::libprotobuf
        amqpcpp
        dl
        backtrace
        PUBLIC
        ${Fruit_LIBS}
)