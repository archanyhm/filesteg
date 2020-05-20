set(
    SOURCE_FILES
    "cmdparse.cpp"
    )
set(
    HEADER_FILES
    "cmdparse.hpp"
    )

add_library(CMDParse ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(CMDParse PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
