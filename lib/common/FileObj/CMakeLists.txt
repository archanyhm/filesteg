set(
    SOURCE_FILES
    "fileobj.cpp"
    )
set(
    HEADER_FILES
    "fileobj.hpp"
    )

add_library(FileObj ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(FileObj PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
