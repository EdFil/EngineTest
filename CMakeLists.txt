cmake_minimum_required(VERSION 3.9)
project(EngineTest LANGUAGES CXX)

message(STATUS "")
message(STATUS "============== ${PROJECT_NAME} ==============")

# ================
# Check build type
# ================

include("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/engine/cmake/Init.cmake")

# ============
# Dependencies
# ============

# Engine
set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources" CACHE PATH "Resources Path" FORCE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/engine")

# ================
# Source gathering
# ================

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.c" "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.h")

# Make library
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} Engine_Static)
target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_DIR})

# Copy resources to build dir
include("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/engine/cmake/SetupResources.cmake")

# Source group generation for IDEs
foreach(SOURCE IN ITEMS ${SOURCES})
    get_filename_component(SOURCE_PATH "${SOURCE}" PATH)
    file(RELATIVE_PATH SOURCE_PATH_REL "${SOURCE_DIR}/.." "${SOURCE_PATH}")
    string(REPLACE "/" "\\" GROUP_PATH "${SOURCE_PATH_REL}")
    source_group("${GROUP_PATH}" FILES "${SOURCE}")
endforeach()

if(MSVC)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()
