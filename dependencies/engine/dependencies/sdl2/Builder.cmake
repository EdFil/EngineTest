# Source builds disabled on Linux because of a bug
if(${USE_PREBUILT_LIBRARIES} OR UNIX AND NOT APPLE)
  message(STATUS "=== SDL2 (Prebuilt) ===")
  include("${CMAKE_CURRENT_LIST_DIR}/prebuilt/Prebuilt.cmake")
else()
  message(STATUS "=== SDL2 (Source) ===")
  set(SDL_STATIC OFF CACHE BOOL "Build a static version of the library" FORCE)
  set(SDL_SHARED ON CACHE BOOL "Build a shared version of the library" FORCE)
  add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/source")
endif()

message(STATUS "")
