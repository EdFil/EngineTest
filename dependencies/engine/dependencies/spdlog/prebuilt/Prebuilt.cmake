if(WIN32)
  set(SPDLOG_DIR ${CMAKE_CURRENT_LIST_DIR}/windows)
  set(SPDLOG_LIB ${SPDLOG_DIR}/lib/spdlog.lib)
elseif (UNIX AND NOT APPLE)
  set(SPDLOG_DIR ${CMAKE_CURRENT_LIST_DIR}/linux)
  set(SPDLOG_LIB ${SPDLOG_DIR}/lib/libspdlog.a)
else()
  message(FATAL_ERROR "NOT IMPLEMENTED")
endif()

add_library(spdlog STATIC IMPORTED GLOBAL)
set_target_properties(
  spdlog PROPERTIES IMPORTED_LOCATION "${SPDLOG_LIB}"
                   INTERFACE_INCLUDE_DIRECTORIES "${SPDLOG_DIR}/include")


message(STATUS "Version: 1.8.1")  

# Source group generation for IDEs
foreach(SOURCE IN ITEMS "${SPDLOG_DIR}/include")
  get_filename_component(SOURCE_PATH "${SOURCE}" PATH)
  file(RELATIVE_PATH SOURCE_PATH_REL "${SOURCE_DIR}/.." "${SOURCE_PATH}")
  string(REPLACE "/" "\\" GROUP_PATH "${SOURCE_PATH_REL}")
  source_group("${GROUP_PATH}" FILES "${SOURCE}")
endforeach()
