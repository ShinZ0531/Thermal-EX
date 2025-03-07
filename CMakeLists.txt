cmake_minimum_required(VERSION 3.7.0)

project(Thermal-EX VERSION 1.0.0 LANGUAGES CXX)

configure_file(${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_BINARY_DIR}/config.h @ONLY)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -pedantic)

add_library(Arknights Arknights.cpp)

add_executable(helloworld
    helloworld.cpp
)

target_link_libraries(helloworld Arknights)