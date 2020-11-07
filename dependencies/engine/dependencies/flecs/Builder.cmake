if(${USE_PREBUILT_LIBRARIES})
  message(STATUS "=== FLECS (Prebuilt) ===")
  include("${CMAKE_CURRENT_LIST_DIR}/prebuilt/Prebuilt.cmake")
else()
  message(STATUS "=== FLECS (Source) ===")
  add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/source")
endif()

message(STATUS "")