cmake_minimum_required(VERSION 3.16)
project(audio_controller)

set(CMAKE_CXX_STANDARD 17)


set(impl_headers

        impl/tasks/manage_speaker_audio_task_impl/manage_speaker_audio_task_impl.h

        impl/sound_controller.h
        impl/sound_controller/sound_controller_impl.h
        )

set(controller_sources )
if (WIN32)
    list(APPEND impl_headers "impl/sound_controller/win32/sound_controller_win32_impl.h")
    list(APPEND controller_sources "impl/sound_controller/win32/sound_controller_win32_impl.cpp")
else ()
    list(APPEND impl_headers "impl/sound_controller/linux/sound_controller_linux_impl.h")
    list(APPEND controller_sources "impl/sound_controller/linux/sound_controller_linux_impl.cpp")
endif ()

add_library(
        audio_controller_lib
        audio_controller.cpp

        impl/tasks/tasks.cpp
        impl/tasks/manage_speaker_audio_task_impl/manage_speaker_audio_task_impl.cpp

        ${controller_sources}

        ${impl_headers}
)


target_include_directories(
        audio_controller_lib
        PRIVATE
        impl
        interfaces
        PUBLIC
        include
)

add_executable(
        audio_controller_standalone
        main.cpp
)

if(WIN32)
target_compile_definitions(
        audio_controller_lib
        PUBLIC
        UNICODE
)
endif()

target_link_libraries(
        audio_controller_standalone
        audio_controller_lib
)

install_project_binaries(audio_controller_standalone)
