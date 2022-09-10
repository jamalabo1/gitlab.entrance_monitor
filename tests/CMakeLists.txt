cmake_minimum_required(VERSION 3.16)
project(tests)

set(CMAKE_CXX_STANDARD 17)

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

# create a variable to append all test sources to it. https://stackoverflow.com/a/33432463/7615694
# maybe change this to use macro.
set(TEST_SOURCES "")

add_subdirectory(utils)

add_executable(tests_exc ${TEST_SOURCES})
target_link_libraries(tests_exc GTest::GTest GTest::Main)
gtest_discover_tests(tests_exc) # integration with CTest
