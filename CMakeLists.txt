cmake_minimum_required(VERSION 3.7.0)

project(cmake-hello-world VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -pedantic)

add_library(mult5 mult5.cpp)

add_executable(helloworld
    helloworld.cpp
)

target_link_libraries(helloworld mult5)

enable_testing()
add_executable(test_mult5 test_mult5.cpp)
target_link_libraries(test_mult5 mult5)
add_test(TestMult5 test_mult5)