cmake_minimum_required(VERSION 3.16)
project(src)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED log)
find_package(Fruit REQUIRED)

include_directories(${FRUIT_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} models)

link_libraries(${Fruit_LIBS} ${Boost_LIBRARIES})

add_subdirectory(core)

link_libraries(core)
link_directories(core)

add_subdirectory(utils)

link_libraries(utils)
link_directories(utils)


add_subdirectory(blocking_computation)
add_subdirectory(object_detector)
add_subdirectory(results_aggregator)
add_subdirectory(stream_obtainer)
add_subdirectory(audio_controller)
