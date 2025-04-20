cmake_minimum_required(VERSION 3.7.0)

project(Thermal-EX DESCRIPTION "Ultrasonic-HCSR04, LED" VERSION 2.2.1 LANGUAGES CXX)
include(GNUInstallDirs)

configure_file(${CMAKE_SOURCE_DIR}/src/Arknights/config.h.in ${CMAKE_SOURCE_DIR}/src/Arknights/config.h @ONLY)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -pedantic)

add_subdirectory(tests)

find_package(PkgConfig REQUIRED)  
pkg_check_modules(GPIOD REQUIRED libgpiod) 


add_library(Arknights STATIC
    src/Arknights/Arknights.cpp
)

add_library(LED STATIC
    src/LED/LEDController.cpp
)

add_library(HCSR04 STATIC
    src/Ultrasonic/HCSR04.cpp
)

add_library(SG90 STATIC
    src/SG90/SG90Controller.cpp
)

add_library(Keyboard STATIC
    src/Keyboard/KeyboardInputMonitor.cpp
)

target_link_libraries(LED gpiod)
target_link_libraries(HCSR04 gpiod)
target_link_libraries(SG90 gpiod)

include_directories(src)
file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/*.h
)
set(CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/src/Config.h)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})