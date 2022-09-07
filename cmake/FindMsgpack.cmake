find_path(
        Msgpack_INCLUDE_DIR msgpack/msgpack.hpp
        HINTS $ENV{Msgpack_DIR}
        PATH_SUFFIXES include/msgpack include msgpack
)

#include(${CMAKE_MODULE_PATH}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Msgpack DEFAULT_MSG Msgpack_INCLUDE_DIR)