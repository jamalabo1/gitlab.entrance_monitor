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
