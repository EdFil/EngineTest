message(STATUS "=== GLM (Source) ===")
set(BUILD_STATIC_LIBS ON CACHE BOOL "")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/source/glm")
message(STATUS "Version: 0.9.9.8")

message(STATUS "")