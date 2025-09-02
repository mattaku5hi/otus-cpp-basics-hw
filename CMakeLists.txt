cmake_minimum_required(VERSION 3.12)

project(01.hello_world)

set(CURDIR ${CMAKE_SOURCE_DIR})

add_executable(${PROJECT_NAME} 
    example.cpp
    hello_world.cpp
    move_me_out.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CURDIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -std=c++23     
    -fpermissive
    -Wextra
    -pedantic
    -O
    -g
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    stdc++exp
)
