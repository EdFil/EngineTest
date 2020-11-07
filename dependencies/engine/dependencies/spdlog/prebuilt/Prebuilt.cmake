if(WIN32)
  message(FATAL_ERROR "NOT IMPLEMENTED")
elseif (UNIX AND NOT APPLE)
  set(SPDLOG_DIR ${CMAKE_CURRENT_LIST_DIR}/linux)
else()
  message(FATAL_ERROR "NOT IMPLEMENTED")
endif()

find_package(spdlog REQUIRED PATHS ${SPDLOG_DIR})

message(STATUS "Version: ${spdlog_VERSION}")  

# Source group generation for IDEs
foreach(SOURCE IN ITEMS ${FLECS_INCLUDE_DIR})
  get_filename_component(SOURCE_PATH "${SOURCE}" PATH)
  file(RELATIVE_PATH SOURCE_PATH_REL "${SOURCE_DIR}/.." "${SOURCE_PATH}")
  string(REPLACE "/" "\\" GROUP_PATH "${SOURCE_PATH_REL}")
  source_group("${GROUP_PATH}" FILES "${SOURCE}")
endforeach()
