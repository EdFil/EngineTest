if(WIN32)
  set(SDL2_DIR "${CMAKE_CURRENT_LIST_DIR}/windows")
  set(SDL2_LIB "${SDL2_DIR}/lib/SDL2.lib")
  set(SDL2main_LIB "${SDL2_DIR}/lib/SDL2main.lib")
  set(SDL2_RUNTIME_LIB "${SDL2_DIR}/lib/SDL2.dll")

  file(INSTALL ${SDL2_RUNTIME_LIB} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
elseif (UNIX AND NOT APPLE)
  set(SDL2_DIR "${CMAKE_CURRENT_LIST_DIR}/linux")
  set(SDL2_LIB "${SDL2_DIR}/lib/libSDL2.a")
  set(SDL2main_LIB "${SDL2_DIR}/lib/libSDL2main.a")
else()
message(FATAL_ERROR "NOT IMPLEMENTED")
endif()

set(SDL2_VERSION "2.0.12")
set(SDL2_INCLUDE_DIR ${SDL2_DIR}/include)

add_library(SDL2 STATIC IMPORTED GLOBAL)
set_target_properties(SDL2 PROPERTIES 
    IMPORTED_LOCATION "${SDL2_LIB}" 
    INTERFACE_INCLUDE_DIRECTORIES "${SDL2_INCLUDE_DIR}")

add_library(SDL2main STATIC IMPORTED GLOBAL)
set_target_properties(SDL2main PROPERTIES IMPORTED_LOCATION "${SDL2main_LIB}")

message(STATUS "Version: ${SDL2_VERSION}")
message(STATUS "Libs: ${SDL2_LIBS} ${SDL2_RUNTIME_LIB}")
message(STATUS "Include Dirs: ${SDL2_INCLUDE_DIR}")

# Source group generation for IDEs
foreach(SOURCE IN ITEMS ${SDL2_INCLUDE_DIR})
  get_filename_component(SOURCE_PATH "${SOURCE}" PATH)
  file(RELATIVE_PATH SOURCE_PATH_REL "${SOURCE_DIR}/.." "${SOURCE_PATH}")
  string(REPLACE "/" "\\" GROUP_PATH "${SOURCE_PATH_REL}")
  source_group("${GROUP_PATH}" FILES "${SOURCE}")
endforeach()
