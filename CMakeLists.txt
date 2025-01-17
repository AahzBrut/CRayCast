cmake_minimum_required(VERSION 3.30)
project(CRayCast C)

set(CMAKE_C_STANDARD 23)

SET(BUILD_SHARED_LIBS OFF)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raylib)

add_executable(CRayCast CRayCast/main.c
        CRayCast/constants.h)

target_link_libraries(CRayCast PUBLIC raylib)

add_custom_target(COPY_ASSETS
        COMMAND
        ${CMAKE_COMMAND} -E copy_directory_if_different
        "${CMAKE_CURRENT_LIST_DIR}/assets" "${CMAKE_CURRENT_BINARY_DIR}/assets"
)
add_dependencies(${CMAKE_PROJECT_NAME} COPY_ASSETS)