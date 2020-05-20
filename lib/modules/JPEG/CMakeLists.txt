set(
    JPEG_SOURCES
    "append.hpp"
    )
set(
    JPEG_HEADERS
    "append.cpp"
    )

add_library(JPEG ${JPEG_SOURCES} ${JPEG_HEADERS})
target_include_directories(JPEG PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
