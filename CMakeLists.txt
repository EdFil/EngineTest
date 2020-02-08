cmake_minimum_required(VERSION 3.6)
project(EngineTest VERSION 0 LANGUAGES CXX)

# Variable definitions
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_CXX_STANDARD 17)

set(CMAKE_PROJECT_VERSION "0.0.0")
set(CMAKE_PROJECT_VERSION_MAJOR "0")
set(CMAKE_PROJECT_VERSION_MINOR "0")
set(CMAKE_PROJECT_VERSION_PATCH "0")

message(STATUS "")
message(STATUS "============== ${PROJECT_NAME} ==============")
message(STATUS "")

# ================
# Check build type
# ================

set (USE_PREBUILT_LIBRARIES ON)
set (USE_COMPILE_TIME_STRING_ID ON)

if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Debug)
elseif((NOT ${CMAKE_BUILD_TYPE} STREQUAL Debug) AND (NOT ${CMAKE_BUILD_TYPE} STREQUAL Release))
    message(FATAL_ERROR " --> 'CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}' <--> Possible Values: [Debug|Release]'")
endif()
message(STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

# ===========
# Build flags
# ===========

if (MSVC)
    set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /EHsc /W3 /experimental:external /external:anglebrackets /external:W0")
    set(CMAKE_CXX_FLAGS_DEBUG "/MDd /Zi /Ob0 /Od /RTC1 /DDEBUG /DSDL_ASSERT_LEVEL=2")
    set(CMAKE_CXX_FLAGS_RELEASE "/MD /Ox /Ob2 /DRELEASE /DSDL_ASSERT_LEVEL=0")
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -fno-exceptions")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -DDEBUG -DSDL_ASSERT_LEVEL=2")
    set(CMAKE_CXX_FLAGS_RELEASE "-DRELEASE -DSDL_ASSERT_LEVEL=0")
endif()

# ============
# Dependencies
# ============

# Engine
set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources" CACHE PATH "Resources Path" FORCE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/engine")

# ================
# Source gathering
# ================

set (SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE SOURCES
        "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.c"
        "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.h")

# Make library
add_executable(${PROJECT_NAME} ${SOURCES})

# Add libs/projects to link against
target_link_libraries(${PROJECT_NAME} Engine_Static)

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_DIR})

# Copy resources to build dir
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCES_DIR} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources)

# Source group generation for IDEs
foreach(SOURCE IN ITEMS ${SOURCES})
    get_filename_component(SOURCE_PATH "${SOURCE}" PATH)
    file(RELATIVE_PATH SOURCE_PATH_REL "${SOURCE_DIR}/.." "${SOURCE_PATH}")
    string(REPLACE "/" "\\" GROUP_PATH "${SOURCE_PATH_REL}")
    source_group("${GROUP_PATH}" FILES "${SOURCE}")
endforeach()