cmake_minimum_required(VERSION 3.5)

project(filesteg
        VERSION 0.0.1
        DESCRIPTION "Simple stegonography tool"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB HEADER_FILES CONFIGURE_DEPENDS ${filesteg_SOURCE_DIR}/lib/*.hpp)
file(GLOB SOURCE_FILES ${filesteg_SOURCE_DIR}/src/*.cpp)

include_directories(${filesteg_SOURCE_DIR}/lib)

add_compile_options("-Wall")
add_compile_options("-Wextra")

if(MINGW OR WIN32)
    link_libraries(-static-libgcc -static-libstdc++)
    link_libraries(-static pthread)
endif()

## ----- Some configuration options ------ ##
option(DEBUG__SHOW_STAT_INFO "Prints sys/stat.h information on the executable" OFF)
option(CONFIG__ALLOW_INTERACTIVE "Allows interactive mode of the program" OFF)

if(DEBUG__SHOW_STAT_INFO)
    add_definitions(-DDEBUG__SHOW_STAT_INFO)
endif()
if(CONFIG__ALLOW_INTERACTIVE)
    add_compile_definitions(CONFIG__ALLOW_INTERACTIVE)
endif()
## --------------------------------------- ##

add_executable(filesteg ${SOURCE_FILES} ${HEADER_FILES})

source_group(TREE "${filesteg_SOURCE_DIR}/lib" PREFIX "Header Files" FILES ${HEADER_FILES})
source_group(TREE "${filesteg_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${SOURCE_FILES})
