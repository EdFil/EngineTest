if(WIN32)
    # Check architecture so we can set correct paths
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(VC_LIB_PATH_SUFFIX lib/x64)
    else()
        set(VC_LIB_PATH_SUFFIX lib/x86)
    endif()

    set(FLECS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/windows)
    set(FLECS_INCLUDE_DIR ${FLECS_DIR}/include)
    set(FLECS_LIBRARY ${FLECS_DIR}/${VC_LIB_PATH_SUFFIX}/flecs_static.lib)

    add_library(flecs_static STATIC IMPORTED GLOBAL)
    set_target_properties(flecs_static
        PROPERTIES
        IMPORTED_IMPLIB ${FLECS_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${FLECS_INCLUDE_DIR}
    )

    message(STATUS ${FLECS_LIBRARY})

    # Source group generation for IDEs
    foreach(SOURCE IN ITEMS ${FLECS_INCLUDE_DIR})
        get_filename_component(SOURCE_PATH "${SOURCE}" PATH)
        file(RELATIVE_PATH SOURCE_PATH_REL "${SOURCE_DIR}/.." "${SOURCE_PATH}")
        string(REPLACE "/" "\\" GROUP_PATH "${SOURCE_PATH_REL}")
        source_group("${GROUP_PATH}" FILES "${SOURCE}")
    endforeach()
else()
    message(FATAL_ERROR "NOT IMPLEMENTED")
endif()