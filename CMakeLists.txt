cmake_minimum_required(VERSION 3.28)

project(TetrisCustom VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

set(LIBRARY_NAME "Library")
set(EXECUTABLE_NAME "Executable")


option(ENABLE_WARNINGS "Enable compiler warnings for a target" ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable compiler warnings as errors" OFF)



set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

if(ENABLE_WARNINGS)
    include(Warnings)
endif()

if(ENABLE_SANITIZE_ADDR OR ENABLE_SANITIZE_UNDEF)
    include(Sanitizer)
    add_sanitizer_flags()
endif()

add_subdirectory(src)
add_subdirectory(app)


include(CPM)
cpmaddpackage("gh:raysan5/raylib#5.0")
