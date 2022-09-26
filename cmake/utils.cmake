function(install_project_binaries target)
    #    install_amqpclient_binaries(${target})
endfunction()

macro(expose_target _target_prefix target_prefix)
    #    string(REPLACE "_" "-" output ${target_prefix})
    #    message(STATUS ${target_prefix})

    set(_TARGET_LIB "${_target_prefix}_lib")
    set(_TARGET_STANDALONE "${_target_prefix}_standalone")

    set(TARGET_LIB "${target_prefix}-lib")
    set(TARGET_STANDALONE "${target_prefix}-standalone")

    #    add_custom_target(
    #            ${TARGET_LIB}
    #    )
    #    target_link_libraries(
    #            ${TARGET_LIB}
    #            ${_TARGET_LIB}
    #    )

    add_library(${TARGET_LIB} ALIAS ${_TARGET_LIB})
    add_executable(${TARGET_STANDALONE} ALIAS ${_TARGET_STANDALONE})
endmacro()

macro(expose_testable_target target)

endmacro()

# a macro for creating a test target, link a supplied target to a executable with gtest, and link the target to test (core_tests target wants to test core target)
# this implies that a library target staffing ${test_target_prefix}_tests exists.
macro(create_testing_target test_target_prefix)
    enable_testing()
    find_package(GTest REQUIRED)
    include(GoogleTest)

    set(target_to_test ${test_target_prefix})
    set(test_target "${test_target_prefix}_tests")
    set(test_target_exc "${test_target}_exc")


    target_link_libraries(${test_target} PUBLIC ${target_to_test})

#    target_link_libraries (${test_target} PUBLIC $<TARGET_PROPERTY:${target_to_test},LINK_LIBRARIES> )
    target_include_directories (${test_target} PUBLIC $<TARGET_PROPERTY:${target_to_test},private_include_directories>)

    target_link_libraries(${global_test_target} PRIVATE $<TARGET_OBJECTS:${test_target}> ${test_target})

    create_testing_executable(${test_target} ${test_target_exc})
endmacro()


macro(create_testing_executable test_target test_target_exc)
    target_link_libraries(${test_target} PUBLIC GTest::gtest GTest::gmock) # link with gtest to register all tests.

    add_executable(${test_target_exc} $<TARGET_OBJECTS:${test_target}>) # add a executable with test_target objects.

    target_link_libraries(${test_target_exc} ${test_target} GTest::gtest_main) # link with gtest_main for a main entrypoint provided by gtest.

    gtest_discover_tests(${test_target_exc}) # integration with CTest
endmacro()

macro(create_global_testing_target global_test_target_name source_files)
    enable_testing()
    find_package(GTest REQUIRED)
    include(GoogleTest)


    set(global_test_target ${global_test_target_name})
    set(test_target ${global_test_target})

    add_library(${test_target} ${source_files})
endmacro()

macro(enable_global_testing_target)
    set(target_name_exc "${test_target}_exc")

    create_testing_executable(${test_target} ${target_name_exc})

#    add_executable(${exc_target_name} $<TARGET_OBJECTS:${test_target}>) # add a executable with test_target objects.
#
#    target_link_libraries(${exc_target_name} ${test_target} GTest::gtest) # link with gtest_main for a main entrypoint provided by gtest.
#
#    gtest_discover_tests(${exc_target_name}) # integration with CTest
endmacro()
