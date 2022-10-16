cmake_minimum_required(VERSION 3.16)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules")
include(AzureVcpkg)
az_vcpkg_integrate()

project(entrance_monitor_v2 VERSION 0.0.1 DESCRIPTION "entrance monitoring project")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

include(utils)

### set project default variables

set_default(PROJECT_IS_LOCAL OFF)

set_default(CORE_USE_AZURE_KEYVAULT ON)

## end set project variables

add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(tests)