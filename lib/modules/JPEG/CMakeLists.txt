set(
    JPEG_SOURCES
    "jpeg__config.cpp"
    "jpeg__identify.cpp"
    "jpeg__check_append.cpp"
    "jpeg__append_payload.cpp"
    )
set(
    JPEG_HEADERS
    "jpeg__config.hpp"
    "jpeg__identify.hpp"
    "jpeg__check_append.hpp"
    "jpeg__append_payload.hpp"
    )

add_library(JPEG ${JPEG_SOURCES} ${JPEG_HEADERS})
target_include_directories(JPEG PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(JPEG PUBLIC return_types)
target_link_libraries(JPEG PUBLIC FileObj)
