include(core)

find_path(
        FRUIT_INCLUDE_DIR fruit/fruit.h
        HINTS $ENV{Fruit_DIR}
        PATH_SUFFIXES include/fruit include fruit
)

find_library(
        Fruit_LIBS
        NAMES fruit
        HINTS $ENV{Fruit_DIR}
        PATH_SUFFIXES "lib/${LINK_LIB_FOLDER}" ${FRUIT_INSTALLED_DIR}
)


#include(${CMAKE_MODULE_PATH}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Fruit DEFAULT_MSG Fruit_LIBS FRUIT_INCLUDE_DIR)
