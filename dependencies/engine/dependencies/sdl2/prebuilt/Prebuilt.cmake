if(WIN32)
  set(SDL2_VERSION "2.0.12")
  set(SDL2_INCLUDE_DIR ${SDL2_DIR}/include)
  set(SDL2_DIR "${CMAKE_CURRENT_LIST_DIR}/windows")
  set(SDL2_LIB "${SDL2_DIR}/lib/SDL2.lib")
  set(SDL2main_LIB "${SDL2_DIR}/lib/SDL2main.lib")
  set(SDL2_RUNTIME_LIB "${SDL2_DIR}/lib/SDL2.dll")

  add_library(SDL2main STATIC IMPORTED GLOBAL)
  set_target_properties(SDL2main PROPERTIES IMPORTED_LOCATION "${SDL2main_LIB}")
  

  file(INSTALL ${SDL2_RUNTIME_LIB} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

  message(FATAL_ERROR "Update ME")
elseif (UNIX AND NOT APPLE)
  set(SDL2_PATH "${CMAKE_CURRENT_LIST_DIR}/linux" CACHE STRING "Custom SDL2 Library path" FORCE)
  set(SDL2_NO_DEFAULT_PATH TRUE CACHE BOOL "Disable search SDL2 Library in default path" FORCE)
  
  find_package(SDL2 REQUIRED)
else()
  message(FATAL_ERROR "NOT IMPLEMENTED")
endif()

message(STATUS "Version: ${SDL2_VERSION_STRING}")
message(STATUS "Includes: ${SDL2_INCLUDE_DIRS}")
message(STATUS "Libraries: ${SDL2_LIBRARIES}")

# Source group generation for IDEs
foreach(SOURCE IN ITEMS ${SDL2_INCLUDE_DIRS})
  get_filename_component(SOURCE_PATH "${SOURCE}" PATH)
  file(RELATIVE_PATH SOURCE_PATH_REL "${SDL2_PATH}/.." "${SOURCE_PATH}")
  string(REPLACE "/" "\\" GROUP_PATH "${SOURCE_PATH_REL}")
  source_group("${GROUP_PATH}" FILES "${SOURCE}")
endforeach()
