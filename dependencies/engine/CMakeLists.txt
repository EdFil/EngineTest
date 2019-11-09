project(Engine)
cmake_minimum_required(VERSION 2.8.12)

# Configure CMake
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# CXX Flags
if(MSVC)
	set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /experimental:external /external:anglebrackets /external:W0 /Wall /GR /EHsc")
	if(NOT ${CMAKE_BUILD_TYPE} STREQUAL "Release")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /MTd")
    endif()
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O0 -g")
endif()

if (USE_COMPILE_TIME_STRING_ID)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCOMPILE_TIME_STRING_ID")
endif()

# ============
# Dependencies
# ============

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb")

if(NOT RESOURCES_DIR)
	message(WARNING "RESOURCES_DIR not set")
elseif(NOT IS_DIRECTORY ${RESOURCES_DIR})
	message(WARNING "${RESOURCES_DIR} is not a directory")
endif()
message(STATUS "ENGINE - RESOURCES_DIR = ${RESOURCES_DIR}")

# ================
# Source gathering
# ================

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE SOURCES 
    "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.c"
    "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.h")

if (MSVC)
    list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Engine.natvis")
endif()

# Make library
add_library(Engine_Static STATIC ${SOURCES})

# Include directotories
target_include_directories(Engine_Static 
    PUBLIC
    "${SOURCE_DIR}"
)

# Link dependencies
target_link_libraries(Engine_Static
		PUBLIC
		SDL2 SDL2main # SDL
		stb_static # stb
)

# Source group generation for IDEs
foreach(SOURCE IN ITEMS ${SOURCES})
    get_filename_component(SOURCE_PATH "${SOURCE}" PATH)
    file(RELATIVE_PATH SOURCE_PATH_REL "${SOURCE_DIR}/.." "${SOURCE_PATH}")
    string(REPLACE "/" "\\" GROUP_PATH "${SOURCE_PATH_REL}")
    source_group("${GROUP_PATH}" FILES "${SOURCE}")
endforeach()
