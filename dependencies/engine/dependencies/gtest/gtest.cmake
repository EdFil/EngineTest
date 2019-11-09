cmake_minimum_required(VERSION 2.8.2)
project(gtest-download NONE)

include(ExternalProject)

ExternalProject_Add(gtest
    URL               https://github.com/google/googletest/archive/release-1.10.0.tar.gz
    SOURCE_DIR        "${CMAKE_CURRENT_SOURCE_DIR}/gtest"
    BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/gtest-build"
    BINARY_DIR        ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
    INSTALL_COMMAND   ""
    TEST_COMMAND      ""
)