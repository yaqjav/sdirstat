cmake_minimum_required(VERSION 3.19)
project(sdirstat LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(sdirstat
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

qt_add_resources(sdirstat "app_images"
    PREFIX "/"
    FILES assets/sdirstat.png
)

target_link_libraries(sdirstat
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS sdirstat
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if(WIN32)
    enable_language(RC)
    target_sources(sdirstat PRIVATE assets/sdirstat.rc)
    target_include_directories(sdirstat PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    )
endif()

qt_generate_deploy_app_script(
    TARGET sdirstat
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
