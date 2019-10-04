# Download and unpack SDL2 at configure time
configure_file(SDL2.cmake SDL2-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/SDL2-download
                OUTPUT_QUIET
                ERROR_QUIET)
if(result)
    message(FATAL_ERROR "CMake step for SDL2 failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/SDL2-download
                OUTPUT_QUIET
                ERROR_QUIET)
if(result)
    message(FATAL_ERROR "Build step for SDL2 failed: ${result}")
endif()

if (${USE_PREBUILT_LIBRARIES})
    if(WIN32)
        set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SDL2")
        find_package(SDL2 REQUIRED)

        if (NOT SDL2_INCLUDE_DIR OR NOT SDL2_LIBRARY)
            message (FATAL_ERROR "SDL2 not found. Did it download correctly?")
        endif()

        add_library(SDL2 SHARED IMPORTED GLOBAL)
        set_target_properties(SDL2
            PROPERTIES
            IMPORTED_IMPLIB "${SDL2_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${SDL2_INCLUDE_DIR}"
        )

        add_library(SDL2main SHARED IMPORTED GLOBAL)
        set_target_properties(SDL2main
            PROPERTIES
            IMPORTED_IMPLIB "${SDL2MAIN_LIBRARY}"
        )

        if (WIN32)
            file(INSTALL ${SDL2_RUNTIME_LIBRARY} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
        endif()

        # Source group generation for IDEs
        foreach(SOURCE IN ITEMS ${SDL2_INCLUDE_DIR})
            get_filename_component(SOURCE_PATH "${SOURCE}" PATH)
            file(RELATIVE_PATH SOURCE_PATH_REL "${SOURCE_DIR}/.." "${SOURCE_PATH}")
            string(REPLACE "/" "\\" GROUP_PATH "${SOURCE_PATH_REL}")
            source_group("${GROUP_PATH}" FILES "${SOURCE}")
        endforeach()
    else()
        find_package(SDL2 REQUIRED)

        add_library(SDL2 INTERFACE)
        target_include_directories(SDL2 SYSTEM INTERFACE ${SDL2_INCLUDE_DIR})
        target_link_libraries(SDL2 INTERFACE ${SDL2_LIBRARY})

    endif()
else()
    # Add SDL2 directly to our build. This defines the SDL2 and SDL2main targets.
    add_subdirectory(
        "${CMAKE_CURRENT_SOURCE_DIR}/SDL2"
        "${CMAKE_CURRENT_BINARY_DIR}/SDL2-build"
        EXCLUDE_FROM_ALL)
endif()