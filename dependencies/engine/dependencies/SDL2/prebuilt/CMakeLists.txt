if(WIN32)
    set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/windows")
    find_package(SDL2 REQUIRED)

    if(NOT SDL2_INCLUDE_DIR OR NOT SDL2_LIBRARY)
        message(FATAL_ERROR "SDL2 libs not found in ${SDL2_DIR}")
    endif()

    add_library(SDL2 SHARED IMPORTED GLOBAL)
    set_target_properties(SDL2 PROPERTIES IMPORTED_IMPLIB "${SDL2_LIBRARY}" INTERFACE_INCLUDE_DIRECTORIES
                                                                            "${SDL2_INCLUDE_DIR}")

    add_library(SDL2main SHARED IMPORTED GLOBAL)
    set_target_properties(SDL2main PROPERTIES IMPORTED_IMPLIB "${SDL2MAIN_LIBRARY}")

    file(INSTALL ${SDL2_RUNTIME_LIBRARY} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    # Source group generation for IDEs
    foreach(SOURCE IN ITEMS ${SDL2_INCLUDE_DIR})
        get_filename_component(SOURCE_PATH "${SOURCE}" PATH)
        file(RELATIVE_PATH SOURCE_PATH_REL "${SOURCE_DIR}/.." "${SOURCE_PATH}")
        string(REPLACE "/" "\\" GROUP_PATH "${SOURCE_PATH_REL}")
        source_group("${GROUP_PATH}" FILES "${SOURCE}")
    endforeach()
else()
    find_package(SDL2 REQUIRED)
    message(STATUS "SDL2_VERSION_STRING = ${SDL2_VERSION_STRING}")

    add_library(SDL2 INTERFACE)
    target_include_directories(SDL2 SYSTEM INTERFACE ${SDL2_INCLUDE_DIR})
    target_link_libraries(SDL2 INTERFACE ${SDL2_LIBRARY})

endif()
