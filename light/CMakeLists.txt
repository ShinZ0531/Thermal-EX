cmake_minimum_required(VERSION 3.7.0)

project(Light DESCRIPTION "Demo of LED light for Thermal-EX" VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -pedantic)

find_library(WIRINGPI_LIB wiringPi)

add_executable(light
	light.cpp
)

target_link_libraries(light ${WIRINGPI_LIB})
