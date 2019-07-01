project(STB)
cmake_minimum_required(VERSION 2.8.12)

# Variable definitions
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# Source gathering
file(GLOB_RECURSE SOURCES
        "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.c"
        "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.h")

# Make library
add_library(stb_static INTERFACE)
target_sources(stb_static INTERFACE ${SOURCES})

# Include directotories
target_include_directories(stb_static SYSTEM INTERFACE ${SOURCE_DIR})



