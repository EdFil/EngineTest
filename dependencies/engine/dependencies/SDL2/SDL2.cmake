cmake_minimum_required(VERSION 2.8.2)
project(SDL2-download NONE)

include(ExternalProject)

if (${USE_PREBUILT_LIBRARIES})
    if (MSVC)
    ExternalProject_Add(SDL2
        URL               https://www.libsdl.org/release/SDL2-devel-2.0.9-VC.zip
        SOURCE_DIR        "${CMAKE_CURRENT_SOURCE_DIR}/SDL2"
        BINARY_DIR        ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND     ""
        INSTALL_COMMAND   ""
        TEST_COMMAND      ""
    )
    endif()
else()
    ExternalProject_Add(SDL2
        URL              https://www.libsdl.org/release/SDL2-2.0.9.tar.gz
        SOURCE_DIR        "${CMAKE_CURRENT_SOURCE_DIR}/SDL2"
        BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/SDL2-build"
        BINARY_DIR        ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND     ""
        INSTALL_COMMAND   ""
        TEST_COMMAND      ""
    )
endif()