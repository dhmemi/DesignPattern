cmake_minimum_required(VERSION 3.02)

project(deps)

file(GLOB_RECURSE HDRS include/*.hpp)
file(GLOB_RECURSE SRCS src/*.cpp)
file(GLOB_RECURSE EXAMPLES example/*.cpp)
include_directories(include)
message("add source files: ${HDRS}")
message("add include files: ${SRCS}")
message("add example files:${EXAMPLES}")

add_library(${PROJECT_NAME} ${SRCS} ${HDRS})

foreach(EXAMPLE_FILE ${EXAMPLES})
    get_filename_component(BIN_NAME ${EXAMPLE_FILE} NAME_WE)
    message("add example: ${BIN_NAME}")
    add_executable(${BIN_NAME} ${EXAMPLE_FILE})
    target_link_libraries(${BIN_NAME} ${PROJECT_NAME})
endforeach()