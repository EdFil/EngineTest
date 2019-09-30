# Download and unpack SDL2 at configure time
configure_file(SDL2.cmake SDL2-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/SDL2-download )
if(result)
    message(FATAL_ERROR "CMake step for SDL2 failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/SDL2-download )
if(result)
    message(FATAL_ERROR "Build step for gtest failed: ${result}")
endif()

if (${USE_PREBUILT_LIBRARIES})
    set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SDL2")
    find_package(SDL2 REQUIRED)

    message(STATUS "SDL2_LIBRARY ---> ${SDL2_LIBRARY}")
    message(STATUS "SDL2_RUNTIME_LIBRARY ---> ${SDL2_RUNTIME_LIBRARY}")
    message(STATUS "SDL2_INCLUDE_DIR ---> ${SDL2_INCLUDE_DIR}")
    message(STATUS "SDL2MAIN_LIBRARY ---> ${SDL2MAIN_LIBRARY}")

    add_library(SDL2 SHARED IMPORTED GLOBAL)
    set_target_properties(SDL2
        PROPERTIES
        IMPORTED_IMPLIB "${SDL2_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${SDL2_INCLUDE_DIR}"
    )

    if (WIN32)
        file(INSTALL ${SDL2_RUNTIME_LIBRARY} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    endif()

    add_library(SDL2main SHARED IMPORTED GLOBAL)
    set_target_properties(SDL2main
        PROPERTIES
        IMPORTED_IMPLIB "${SDL2MAIN_LIBRARY}"
    )

else()
    # Add SDL2 directly to our build. This defines the SDL2 and SDL2main targets.
    add_subdirectory(
        "${CMAKE_CURRENT_SOURCE_DIR}/SDL2"
        "${CMAKE_CURRENT_BINARY_DIR}/SDL2-build"
        EXCLUDE_FROM_ALL)
endif()