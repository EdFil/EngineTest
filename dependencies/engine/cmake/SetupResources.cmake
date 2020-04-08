# Copy resources to the executable dir
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCES_DIR}
                                                             ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources)
