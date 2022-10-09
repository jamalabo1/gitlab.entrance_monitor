cmake_minimum_required(VERSION 3.16)
project(src)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS ON)

#set(BOOST_STACKTRACE_LINK ON)
#set(BOOST_STACKTRACE_USE_BACKTRACE ON)
#set(BOOST_STACKTRACE_USE_ADDR2LINE ON)

add_compile_definitions(BOOST_STACKTRACE_LINK BOOST_STACKTRACE_USE_BACKTRACE)

#add_compile_definitions(BOOST_STACKTRACE_LINK BOOST_STACKTRACE_USE_ADDR2LINE)



find_package(Boost COMPONENTS REQUIRED
        log
        stacktrace_backtrace
)
find_package(Fruit REQUIRED)

include_directories(${FRUIT_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} )

link_libraries(${Fruit_LIBS} ${Boost_LIBRARIES})
link_libraries(
        ${Boost_STACKTRACE_BACKTRACE_LIBRARY}
        dl
        backtrace
)

add_subdirectory(models)
link_libraries(view_models)

add_subdirectory(utils)

link_libraries(utils)
#include_directories(utils)

add_subdirectory(core)

link_libraries(core)
#link_directories(core)

add_subdirectory(blocking_computation)
add_subdirectory(object_detector)
add_subdirectory(results_aggregator)
add_subdirectory(stream_obtainer)
add_subdirectory(audio_controller)
