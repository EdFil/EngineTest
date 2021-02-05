project(Engine)
cmake_minimum_required(VERSION 2.8.12)

message(STATUS "")
message(STATUS "============== ${PROJECT_NAME} ==============")

# Configure CMake
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_MESSAGE LAZY)
set(CMAKE_LIBRARY_ARCHITECTURE ${CMAKE_CXX_COMPILER_ARCHITECTURE_ID})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(ENGINE_CMAKE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# CXX Flags
if(USE_COMPILE_TIME_STRING_ID)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCOMPILE_TIME_STRING_ID")
endif()

message(STATUS "")
message(STATUS "CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG = ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE = ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "")

# ============
# Dependencies
# ============
include("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/sdl2/Builder.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/spdlog/Builder.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm/Builder.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew/Builder.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb/Builder.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/flecs/Builder.cmake")
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
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.c"
     "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.h")

if(MSVC)
  list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Engine.natvis")
endif()

# Make library
add_library(Engine_Static STATIC ${SOURCES})

# Include directotories
target_include_directories(Engine_Static PUBLIC "${SOURCE_DIR}" )

# Link dependencies
target_link_libraries(Engine_Static PUBLIC GLEW::GLEW SDL2::Core SDL2::Main ${BGFX_LIBS} stb_static flecs spdlog glm)

# Source group generation for IDEs
foreach(SOURCE IN ITEMS ${SOURCES})
  get_filename_component(SOURCE_PATH "${SOURCE}" PATH)
  file(RELATIVE_PATH SOURCE_PATH_REL "${SOURCE_DIR}/.." "${SOURCE_PATH}")
  string(REPLACE "/" "\\" GROUP_PATH "${SOURCE_PATH_REL}")
  source_group("${GROUP_PATH}" FILES "${SOURCE}")
endforeach()

if(BUILD_TESTS)
  message(STATUS "")
  message(STATUS "=== TESTS ===")

  set(TESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")
  file(GLOB_RECURSE TEST_SOURCES "${TESTS_DIR}/*.cpp" "${TESTS_DIR}/*.c"
       "${TESTS_DIR}/*.hpp" "${TESTS_DIR}/*.h")
  add_executable("${PROJECT_NAME}_tests" ${TEST_SOURCES})

  list(LENGTH TEST_SOURCES NUM_TESTS)
  math(EXPR NUM_TESTS "${NUM_TESTS}-1")
  message(STATUS "We have ${NUM_TESTS} test(s) suite...")

  # Link dependencies
  target_link_libraries(${PROJECT_NAME}_tests PRIVATE Engine_Static gmock_main)
endif()

message(STATUS "")
