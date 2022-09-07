include(core)

find_path(
        SimpleAmqpClient_INCLUDE_DIR SimpleAmqpClient/SimpleAmqpClient.h
        HINTS
        $ENV{SimpleAmqpClient_DIR}
        PATH_SUFFIXES include/SimpleAmqpClient include SimpleAmqpClient
)

SET(SimpleAmqpClient_DIR $ENV{SimpleAmqpClient_DIR})

find_library(
        SimpleAmqpClient_LIBRARY
        NAMES SimpleAmqpClient.7
        PATHS
        ${CMAKE_FIND_ROOT_PATH}
        HINTS ${SimpleAmqpClient_DIR}
        PATH_SUFFIXES "lib/${LINK_LIB_FOLDER}" ${SimpleAmqpClient_INSTALLED_DIR}
)

macro(install_amqpclient_binaries target)
    install_binaries(${target} $ENV{SimpleAmqpClient_DIR})
endmacro()


#include(${CMAKE_MODULE_PATH}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SimpleAmqpClient DEFAULT_MSG SimpleAmqpClient_DIR SimpleAmqpClient_LIBRARY SimpleAmqpClient_INCLUDE_DIR)