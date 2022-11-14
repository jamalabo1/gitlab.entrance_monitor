cmake_minimum_required(VERSION 3.16)
project(models)

#FIND_PACKAGE(Protobuf REQUIRED)


#SET(PROTO_FILES proto/frame_view.proto)
#
#protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
##protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS EXPORT_MACRO DLL_EXPORT ${PROTO_FILES})
##protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS DESCRIPTORS PROTO_DESCS ${PROTO_FILES})
#
##add_executable(bar bar.cc )
#add_library(view_models ${PROTO_SRCS} ${PROTO_HDRS})
#
#target_link_libraries(view_models ${Protobuf_LIBRARY})
#target_link_directories(view_models PUBLIC ${Protobuf_INCLUDE_DIR})
#
#target_include_directories(view_models PUBLIC include .)


# Find required protobuf package
find_package(protobuf REQUIRED)
#include_directories(${PROTOBUF_INCLUDE_DIRS})
if (protobuf_VERBOSE)
    message(STATUS "Using Protocol Buffers ${protobuf_VERSION}")
endif ()
#set(CMAKE_INCLUDE_CURRENT_DIR TRUE)


add_library(
        view_models
        proto/view_models/frame_view.proto
        proto/view_models/detection_result_view.proto
)

target_link_libraries(
        view_models
        PRIVATE
        #        /usr/local/lib/opencv4/3rdparty/liblibprotobuf.a

        #        pthread
        #        /opt/vcpkg/installed/x64-linux/debug/lib/libprotobuf.a
        protobuf::libprotobuf
        protobuf::libprotoc
        ${PROTOBUF_LIBRARIES}
)

target_include_directories(
        view_models
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        PUBLIC
        ${PROTOBUF_INCLUDE_DIRS}
        include
        ${CMAKE_CURRENT_BINARY_DIR}/proto
)

protobuf_generate(TARGET view_models)

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#   message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
#foreach (example view_models)
#    set(${example}_SRCS)
#    set(${example}_PROTOS proto/view_models/frame_view.proto)
#    #Code Generation
#    if (protobuf_MODULE_COMPATIBLE) #Legacy Support
#        list(APPEND ${example}_SRCS ${${example}_PROTO_SRCS} ${${example}_PROTO_HDRS})
#    endif ()
#    #Executable setup
#    set(executable_name ${example})
#    add_library(${executable_name} ${${example}_SRCS} ${${example}_PROTOS})
#
##    if (protobuf_MODULE_COMPATIBLE) #Legacy mode
##        message(STATUS "Using protobuf compatible legacy mode")
##        target_include_directories(${executable_name} PUBLIC ${PROTOBUF_INCLUDE_DIRS})
##        target_link_libraries(${executable_name} ${PROTOBUF_LIBRARIES})
##    else ()
##    endif ()
#    target_link_libraries(${executable_name} PUBLIC protobuf::libprotobuf protobuf::libprotoc ${PROTOBUF_LIBRARIES})
#
#    message(STATUS "BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR},PROTOBUF_LIBRARIES=${PROTOBUF_LIBRARIES},PROTOBUF_INCLUDE_DIRS=${PROTOBUF_INCLUDE_DIRS}")
#    target_include_directories(${executable_name} PUBLIC ${PROTOBUF_INCLUDE_DIRS})
#    target_include_directories(${executable_name} PUBLIC include proto ${CMAKE_CURRENT_BINARY_DIR}/proto PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
#
#    protobuf_generate(TARGET ${executable_name})
#endforeach ()
