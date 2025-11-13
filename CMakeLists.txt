cmake_minimum_required(VERSION 3.28)
project(snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use static runtime library for MSVC
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()


# For single-config generators 
if(NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# For multi-config generators 
else()
    foreach(OUTPUTCONFIG IN LISTS CMAKE_CONFIGURATION_TYPES)
        string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER}
            ${CMAKE_BINARY_DIR}/bin/${OUTPUTCONFIG})
    endforeach()
endif()

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS 'include'/*.hpp)

if(WIN32)
    set(APP_ICON "${CMAKE_CURRENT_SOURCE_DIR}/misc/appicon.ico")
    set(APP_RC "${CMAKE_CURRENT_BINARY_DIR}/appicon.rc")
    file(WRITE ${APP_RC} "IDI_ICON1 ICON \"${APP_ICON}\"\n")
    list(APPEND SOURCES ${APP_RC})
endif()

add_executable(snake
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(snake 
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(snake
    PRIVATE 
        SFML::Graphics
)

# Disable terminal in release mode on Windows
if (WIN32)
    if (MINGW)
        set_target_properties(snake PROPERTIES
            LINK_FLAGS_DEBUG "-mconsole -static"
            LINK_FLAGS_RELEASE "-mwindows -static"
        )
    elseif (MSVC)
        set_target_properties(snake PROPERTIES
            LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
            LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
        )
    endif()
endif()
# Ensure assets can be acessed by executable
add_custom_command(TARGET snake POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:snake>/assets
)

