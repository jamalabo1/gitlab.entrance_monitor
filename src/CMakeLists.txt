cmake_minimum_required(VERSION 3.16)
project(src)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS ON)

add_compile_definitions(BOOST_STACKTRACE_LINK BOOST_STACKTRACE_USE_BACKTRACE)

find_package(Boost COMPONENTS REQUIRED
        log
        stacktrace_backtrace
        )
find_package(Fruit REQUIRED)

include_directories(${FRUIT_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

link_libraries(${Fruit_LIBS} ${Boost_LIBRARIES})

add_subdirectory(models)
link_libraries(view_models)

add_subdirectory(core)
link_libraries(core)

add_subdirectory(services)

#foreach (target stream_obtainer object_detector)
#    target_link_libraries(${target}_lib PRIVATE ${Fruit_LIBS} ${Boost_LIBRARIES})
#endforeach ()
