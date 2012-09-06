set(png_directory libpng-1.5.12)

# We can't build both concurrently because a shared png on MSVC causes link
# errors against a static zlib

if(BUILD_SHARED_LIBS)
    set(PNG_SHARED ON)
    set(PNG_STATIC OFF)
else()
    set(PNG_SHARED OFF)
    set(PNG_STATIC ON)
endif()

if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${png_directory}")
    add_subdirectory(${png_directory})
endif()

# Allow users to rename the library that gets built

if(CMAKEPORTS_NAME_PREFIX AND (TARGET png15 OR TARGET png15_static))
    if(PNG_SHARED)
        set_target_properties(png15 PROPERTIES OUTPUT_NAME "${CMAKEPORTS_NAME_PREFIX}png15")
    endif()
    if(PNG_STATIC)
        set_target_properties(png15_static PROPERTIES OUTPUT_NAME "${CMAKEPORTS_NAME_PREFIX}png15")
    endif()
endif()

# Hide these cache variables so as not to confuse CMakePorts users

if(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION} VERSION_GREATER 2.6.2)
    unset(PNG_STATIC CACHE)
    unset(PNG_SHARED CACHE)
endif()

# Compatibility settings for interoperability with FindPNG.cmake

if(ZLIB_FOUND)
    set(PNG_PNG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${png_directory} PARENT_SCOPE)
    set(PNG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${png_directory} ${ZLIB_INCLUDE_DIR}" PARENT_SCOPE)
    if(PNG_SHARED)
        set(PNG_LIBRARY png15 PARENT_SCOPE)
        set(PNG_LIBRARIES png15 ${ZLIB_LIBRARY} PARENT_SCOPE)
    else()
        set(PNG_LIBRARY png15_static PARENT_SCOPE)
        set(PNG_LIBRARIES png15_static ${ZLIB_LIBRARY} PARENT_SCOPE)
    endif()
    if(CYGWIN AND NOT BUILD_SHARED_LIBS)
        set(PNG_DEFINITIONS -DPNG_STATIC PARENT_SCOPE)
    endif()
    set(PNG_FOUND true PARENT_SCOPE)
endif()

