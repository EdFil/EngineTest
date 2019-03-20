project(EngineTest)
cmake_minimum_required(VERSION 2.8)

# Variable definitions
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set (SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set (CMAKE_CXX_STANDARD 17)

message(STATUS "")
message(STATUS "============== ${PROJECT_NAME} ==============")
message(STATUS "")

# ================
# Check build type
# ================

if (NOT CMAKE_BUILD_TYPE)
    message(WARNING " --> 'CMAKE_BUILD_TYPE' is not defined... assuming 'Debug'")
    set (CMAKE_BUILD_TYPE Debug)
elseif((NOT ${CMAKE_BUILD_TYPE} STREQUAL Debug) AND (NOT ${CMAKE_BUILD_TYPE} STREQUAL Release))
    message(FATAL_ERROR " --> 'CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}' <--> Possible Values: [Debug|Release]'")
endif()
message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")

# ===========
# Build flags
# ===========

if (MSVC)
    message (STATUS "No flags for MSVC yet... Using default ones")
else()
    if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O0 -g -DDEBUG")
        message (STATUS "CMAKE_CXX_FLAGS_DEBUG=${CMAKE_CXX_FLAGS_DEBUG}")
    else()
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -DRELEASE")
        message (STATUS "CMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}")
    endif()
endif()

message (STATUS "CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")

# ============
# Dependencies
# ============

#set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources" CACHE PATH "Resources Path" FORCE)
#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/.." "${CMAKE_BINARY_DIR}/EngineBuild")

# ================
# Source gathering
# ================

file(GLOB_RECURSE SOURCES
        "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.c"
        "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.h")

# Make library
add_executable(${PROJECT_NAME} ${SOURCES})

#target_link_libraries(Engine_TESTS Engine_Static )

# Include directotories
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_DIR})

## Copy resources to build dir
#add_custom_command(TARGET Engine_TESTS POST_BUILD
#		COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCES_DIR} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources)
