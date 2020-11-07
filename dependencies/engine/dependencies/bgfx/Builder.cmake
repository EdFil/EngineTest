if(${USE_PREBUILT_LIBRARIES})
  message(STATUS "=== BGFX (Prebuilt) ===")
  include("${CMAKE_CURRENT_LIST_DIR}/prebuilt/Prebuilt.cmake")
  set(BGFX_LIBS bgfx::bgfx)
else()
  message(STATUS "=== BGFX (Source) ===")
  set( BGFX_BUILD_TOOLS     OFF CACHE BOOL "Build bgfx tools.")
  set( BGFX_BUILD_EXAMPLES  OFF CACHE BOOL "Build bgfx examples.")
  add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/source")
  set(BGFX_LIBS bgfx)
endif()

message(STATUS "")