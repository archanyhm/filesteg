add_subdirectory("JPEG")

add_library(modules INTERFACE)
target_link_libraries(modules INTERFACE JPEG)
