project(Engine)
cmake_minimum_required(VERSION 3.9)

message(STATUS "")
message(STATUS "============== ${PROJECT_NAME} ==============")

# Configure CMake
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/CompilerWarnings.cmake")

option(ENABLE_COMPILE_TIME_STRING_ID "Enable compile time StringID hashing" ON)
option(ENABLE_PREBUILT_LIBRARIES "Enable prebuilt libs" ON)

if(ENABLE_COMPILE_TIME_STRING_ID)
    message(STATUS "Using compile time StringID hashing")
endif()

if(ENABLE_PREBUILT_LIBRARIES)
    message(STATUS "Using prebuilt libs")
endif()

# ============
# Dependencies
# ============

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb")
message(STATUS "")
message(STATUS "=== Resources ===")
if(NOT RESOURCES_DIR)
    message(WARNING "RESOURCES_DIR not set")
elseif(NOT IS_DIRECTORY ${RESOURCES_DIR})
    message(WARNING "${RESOURCES_DIR} is not a directory")
endif()
message(STATUS "RESOURCES_DIR = ${RESOURCES_DIR}")

# ================
# Source gathering
# ================

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.c" "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.h")

if(MSVC)
    list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Engine.natvis")
endif()

# Make library
add_library(Engine_Static STATIC ${SOURCES})

# Include directotories
target_include_directories(Engine_Static PUBLIC "${SOURCE_DIR}")
set_target_compile_options(Engine_Static)

if(ENABLE_COMPILE_TIME_STRING_ID)
    target_compile_options(Engine_Static PUBLIC "-DCOMPILE_TIME_STRING_ID")
endif()

# Link dependencies
target_link_libraries(Engine_Static PUBLIC SDL2 SDL2main stb_static)

# Source group generation for IDEs
foreach(SOURCE IN ITEMS ${SOURCES})
    get_filename_component(SOURCE_PATH "${SOURCE}" PATH)
    file(RELATIVE_PATH SOURCE_PATH_REL "${SOURCE_DIR}/.." "${SOURCE_PATH}")
    string(REPLACE "/" "\\" GROUP_PATH "${SOURCE_PATH_REL}")
    source_group("${GROUP_PATH}" FILES "${SOURCE}")
endforeach()
