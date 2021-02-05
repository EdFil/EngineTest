if(WIN32)
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/windows")
# else()
#   message(FATAL_ERROR "NOT IMPLEMENTED")
endif()

set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

set (GLEW_USE_STATIC_LIBS TRUE)
find_package(GLEW REQUIRED)

target_link_libraries(GLEW::GLEW 
  INTERFACE ${OPENGL_LIBRARIES}
)

target_compile_definitions(GLEW::GLEW 
  INTERFACE GLEW_STATIC
)

list(APPEND GLEW_LIBRARIES ${OPENGL_LIBRARIES})

message(STATUS "Version: ${GLEW_VERSION}")
message(STATUS "Includes: ${GLEW_INCLUDE_DIRS}")
message(STATUS "Libraries: ${GLEW_LIBRARIES}")