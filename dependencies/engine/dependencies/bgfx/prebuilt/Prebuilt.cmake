if(WIN32)
  set(BGFX_DIR "${CMAKE_CURRENT_LIST_DIR}/windows")
elseif (UNIX AND NOT APPLE)
  set(BGFX_DIR "${CMAKE_CURRENT_LIST_DIR}/linux")
else()
  message(FATAL_ERROR "NOT IMPLEMENTED")
endif()

set(BGFX_INCLUDE_DIR ${BGFX_DIR}/include)

find_package(bgfx REQUIRED PATHS ${BGFX_DIR})

message(STATUS "Version: ${bgfx_VERSION}")

# Source group generation for IDEs
foreach(SOURCE IN ITEMS ${BGFX_INCLUDE_DIR})
  get_filename_component(SOURCE_PATH "${SOURCE}" PATH)
  file(RELATIVE_PATH SOURCE_PATH_REL "${SOURCE_DIR}/.." "${SOURCE_PATH}")
  string(REPLACE "/" "\\" GROUP_PATH "${SOURCE_PATH_REL}")
  source_group("${GROUP_PATH}" FILES "${SOURCE}")
endforeach()
