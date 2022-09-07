include(utils)
#if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#    set(LINK_LIB_FOLDER "Debug")
#else ()
#    set(LINK_LIB_FOLDER "Release")
#endif ()
set(LINK_LIB_FOLDER ${CMAKE_BUILD_TYPE})


#get_target_property(OUT Target LINK_LIBRARIES)
#message(STATUS ${OUT})
function(install_binaries target binaries_dir)
    add_custom_command(
            TARGET "${target}" POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${binaries_dir}/bin/$<CONFIGURATION>"
            $<TARGET_FILE_DIR:${target}>
    )
endfunction()
