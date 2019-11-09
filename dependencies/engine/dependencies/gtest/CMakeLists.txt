# Download and unpack gtest at configure time
configure_file(gtest.cmake gtest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gtest-download
                ERROR_QUIET)
if(result)
    message(FATAL_ERROR "CMake step for gtest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gtest-download
                OUTPUT_QUIET
                ERROR_QUIET)
if(result)
    message(FATAL_ERROR "Build step for SDL2 failed: ${result}")
endif()

# Add gtest directly to our build.
add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/gtest"
    "${CMAKE_CURRENT_BINARY_DIR}/gtest-build"
    EXCLUDE_FROM_ALL)