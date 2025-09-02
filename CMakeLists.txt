cmake_minimum_required(VERSION 3.7.2)
project(crc32_crack CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} 
        src/main.cpp
        src/CRC32.cpp
        inc/CRC32.hpp
        src/IO.cpp
        inc/IO.hpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    .
    inc
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    -DUSE_MULTI_THREADING=1
)

if (MSVC)
    target_compile_options(crc32_crack PUBLIC /W4)
else ()
    target_compile_options(crc32_crack PUBLIC -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
endif ()