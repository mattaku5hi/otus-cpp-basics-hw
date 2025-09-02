cmake_minimum_required(VERSION 3.5)

project(container)
set(PRJ_TEST "${PROJECT_NAME}_test")

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Enable testing support
enable_testing()

# Find GTest
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME}
    "${CMAKE_SOURCE_DIR}/inc/continuous.h"
    "${CMAKE_SOURCE_DIR}/inc/linked_doubly.h"
    "${CMAKE_SOURCE_DIR}/inc/linked_singly.h"   
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
)

# Only build tests in Release mode
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_executable(${PRJ_TEST}
        "${CMAKE_SOURCE_DIR}/tests/test_linked_list.cpp"
        "${CMAKE_SOURCE_DIR}/tests/test_vector.cpp"
        
        "${CMAKE_SOURCE_DIR}/tests/test_main.cpp"
    )

    target_link_libraries(${PRJ_TEST} PRIVATE 
        GTest::GTest
        GTest::Main
    )

    target_include_directories(${PRJ_TEST} PRIVATE inc/)

    # Add test executable
    add_test(NAME ${PRJ_TEST} COMMAND ${PRJ_TEST})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE inc/)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

