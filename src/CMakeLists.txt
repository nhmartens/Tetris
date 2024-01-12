set(LIBRARY_SOURCES
    "block.cpp"
    "blocks.cpp"
    "game.cpp"
    "grid.cpp"
    "position.cpp")

set(LIBRARY_HEADERS
    "block.h"
    "blocks.h"
    "colors.h"
    "game.h"
    "grid.h"
    "position.h")

set(LIBRARY_INCLUDES
    "./"
    "${CMAKE_BINARY_DIR}/configured_files/include")


add_library(${LIBRARY_NAME} STATIC
    ${LIBRARY_SOURCES}
    ${LIBRARY_HEADERS})

target_include_directories(${LIBRARY_NAME} PUBLIC
    ${LIBRARY_INCLUDES})

target_link_libraries(${LIBRARY_NAME} PUBLIC
    raylib
)

if (ENABLE_WARNINGS)
    target_set_warnings(
        ${LIBRARY_NAME}
        ON
        OFF
    )
endif()
