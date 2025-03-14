cmake_minimum_required(VERSION 3.7.0)

project(Thermal-EX DESCRIPTION "Print logo and shine the light, using libgpio." VERSION 1.2.0 LANGUAGES CXX)

configure_file(${CMAKE_SOURCE_DIR}/src/Arknights/config.h.in ${CMAKE_SOURCE_DIR}/src/Arknights/config.h @ONLY)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -pedantic)

find_package(PkgConfig REQUIRED)  
pkg_check_modules(GPIOD REQUIRED libgpiod)  

find_library(WIRINGPI_LIB wiringPi)  
if (NOT WIRINGPI_LIB)  
    message(FATAL_ERROR "wiringPi library not found!")  
endif()  

include_directories(src)

add_library(Arknights 
    src/Arknights/Arknights.cpp
)

add_library(LEDController STATIC
    src/LED/LEDController.cpp
)
target_link_libraries(LEDController PRIVATE ${GPIOD_LIBRARIES})  
target_include_directories(LEDController PUBLIC ${GPIOD_INCLUDE_DIRS})  

add_executable(light  
    src/main.cpp  
)  

target_link_libraries(light PRIVATE 
    ${WIRINGPI_LIB} 
    Arknights 
    LEDController
    ${LIBGPIOD_LIBRARIES})  

target_include_directories(light PRIVATE
    ${LIBGPIOD_INCLUDE_DIRS}
)