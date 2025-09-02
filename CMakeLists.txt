cmake_minimum_required(VERSION 3.5)

project(container)

add_executable(container
    "${CMAKE_SOURCE_DIR}/inc/continuous.h"
    "${CMAKE_SOURCE_DIR}/inc/linked_doubly.h"
    "${CMAKE_SOURCE_DIR}/inc/linked_singly.h"
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
)

target_include_directories(container PRIVATE inc/)
set_target_properties(container PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
