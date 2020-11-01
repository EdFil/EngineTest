if(WIN32)
  set(FLECS_DIR ${CMAKE_CURRENT_LIST_DIR}/windows)
  set(FLECS_LIB ${FLECS_DIR}/lib/flecs.lib)
  set(FLECS_RUNTIME_LIB ${FLECS_DIR}/lib/flecs.dll)

  file(INSTALL ${FLECS_RUNTIME_LIB}
       DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
else()
  message(FATAL_ERROR "NOT IMPLEMENTED")
endif()

set(FLECS_INCLUDE_DIR ${FLECS_DIR}/include)

add_library(flecs STATIC IMPORTED GLOBAL)
set_target_properties(
  flecs PROPERTIES IMPORTED_LOCATION "${FLECS_LIB}"
                   INTERFACE_INCLUDE_DIRECTORIES "${FLECS_DIR}/include")

message(STATUS "Version: From source")
message(STATUS "Include Dir: ${FLECS_INCLUDE_DIR}")

# Source group generation for IDEs
foreach(SOURCE IN ITEMS ${FLECS_INCLUDE_DIR})
  get_filename_component(SOURCE_PATH "${SOURCE}" PATH)
  file(RELATIVE_PATH SOURCE_PATH_REL "${SOURCE_DIR}/.." "${SOURCE_PATH}")
  string(REPLACE "/" "\\" GROUP_PATH "${SOURCE_PATH_REL}")
  source_group("${GROUP_PATH}" FILES "${SOURCE}")
endforeach()
