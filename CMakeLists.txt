cmake_minimum_required(VERSION 3.16)
project(most_used_words CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} 
        src/topk_words.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    .
    inc
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    -DUSE_MULTI_THREADING=1
    -DUSE_SHARED_DICT=1
)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC /W4)
else ()
    target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
endif ()