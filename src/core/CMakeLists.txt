cmake_minimum_required(VERSION 3.16)
project(core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Msgpack REQUIRED)
set(OpenCV_STATIC ON)
find_package(OpenCV REQUIRED)
#find_package(SimpleAmqpClient REQUIRED)
find_package(amqpcpp REQUIRED)

#find_package(Eigen3 IMPORTED  REQUIRED)
find_package(azure-identity-cpp CONFIG REQUIRED)
find_package(azure-security-keyvault-secrets-cpp CONFIG REQUIRED)



#find_package(azure-security-keyvault-keys-cpp CONFIG REQUIRED)
#target_link_libraries(<your project name> PRIVATE Azure::azure-security-keyvault-keys)
#
#get_cmake_property(_variableNames VARIABLES)
#list(SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach ()
#

SET(private_headers
        amqp.h
        consumer_message.h
        interfaces/channel_holder.h

        amqp/channel_holder_impl.h
        amqp/amqp_io_context_impl.h

        impl/consumer_impl.h
        impl/publisher_impl.h
        impl/consumer_factory_impl.h
        impl/publisher_factory.h

        amqp/amqp_io_runner_impl.h
        amqp/amqp_connection_impl.h

        interfaces/amqp/connection.h
        interfaces/amqp/io_context.h

        impl/configuration_impl.h impl/io_runner_impl.h impl/gui_handler_impl.h)


add_library(
        core
        core.cpp
        ptrs.cpp
        paths.cpp
        publisher.cpp
        publisher_factory.cpp
        configurations_impl.cpp
        consumer_factory.cpp
        consumer_impl.cpp

        consumer_message_handler.cpp
        gui_handler_impl.cpp
        consumer_message.cpp
        amqp.cpp
        publisher_impl.cpp
        io_runner_impl.cpp
        task_service.cpp

        amqp/connection_factory.cpp
        amqp/channel_holder_impl.cpp
        amqp/amqp_io_context_impl.cpp
        amqp/amqp_io_runner_impl.cpp
        amqp/amqp_connection_impl.cpp

        ${private_headers}
)

target_link_libraries(core PRIVATE Azure::azure-identity Azure::azure-security-keyvault-secrets )


target_include_directories(
        core
        PRIVATE
        $<TARGET_PROPERTY:amqpcpp,INTERFACE_INCLUDE_DIRECTORIES>
        impl
        interfaces
        PUBLIC
        ${Msgpack_INCLUDE_DIR}
        ${FRUIT_INCLUDE_DIR}
        ${Boost_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        include
)


target_link_libraries(
        core
        PRIVATE
        ${OpenCV_LIBS}
        ${Boost_LIBRARIES}
        ${Fruit_LIBS}
        amqpcpp
)

target_compile_definitions(
        core
        PUBLIC
        NOMINMAX
)
