cmake_minimum_required(VERSION 3.19)
project(sdirstat LANGUAGES CXX)

find_package(Qt6 6.8 REQUIRED COMPONENTS Core Widgets Concurrent)

qt_standard_project_setup()

qt_add_executable(sdirstat
        WIN32 MACOSX_BUNDLE
        src/main.cpp
        src/ui/mainwindow.cpp
        src/ui/mainwindow.h
        src/utils/size_tools.cpp
        src/utils/size_tools.h
        src/scanning/scanner.cpp
        src/scanning/scanner.h
        src/ui/app_menu_bar.cpp
        src/ui/app_menu_bar.cpp
        src/ui/app_menu_bar.h
        src/ui/app_status_bar.cpp
        src/ui/app_status_bar.h
)

target_compile_features(sdirstat PRIVATE cxx_std_17)

target_compile_options(sdirstat PRIVATE
        "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/utf-8>"
)

qt_add_resources(sdirstat "app_images"
        PREFIX "/"
        FILES assets/sdirstat.png
)

target_link_libraries(sdirstat
        PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Concurrent
)

install(TARGETS sdirstat
        BUNDLE DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if (WIN32)
    target_link_libraries(sdirstat PRIVATE psapi)
    enable_language(RC)
    target_sources(sdirstat PRIVATE assets/sdirstat.rc)
    target_include_directories(sdirstat PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    )
endif ()

# Keep the executable runnable from CLion and directly from its build directory.
if (WIN32)
    get_filename_component(SDIRSTAT_COMPILER_BIN "${CMAKE_CXX_COMPILER}" DIRECTORY)
    add_custom_command(TARGET sdirstat POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E env
                "PATH=${SDIRSTAT_COMPILER_BIN};$ENV{PATH}"
                "$<TARGET_FILE:Qt6::windeployqt>"
                --no-translations --compiler-runtime
                "$<TARGET_FILE:sdirstat>"
            VERBATIM
    )
    if (MINGW)
        add_custom_command(TARGET sdirstat POST_BUILD
                COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                    "${SDIRSTAT_COMPILER_BIN}/libgcc_s_seh-1.dll"
                    "${SDIRSTAT_COMPILER_BIN}/libstdc++-6.dll"
                    "${SDIRSTAT_COMPILER_BIN}/libwinpthread-1.dll"
                    "$<TARGET_FILE_DIR:sdirstat>"
                VERBATIM
        )
    endif ()
endif ()

qt_generate_deploy_app_script(
        TARGET sdirstat
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
