cmake_minimum_required(VERSION 3.7.0)

project(Thermal-EX DESCRIPTION "Print logo and shine the light." VERSION 1.1.0 LANGUAGES CXX)

configure_file(${CMAKE_SOURCE_DIR}/src/Arknights/config.h.in ${CMAKE_SOURCE_DIR}/src/Arknights/config.h @ONLY)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -pedantic)


find_library(WIRINGPI_LIB wiringPi)  
if (NOT WIRINGPI_LIB)  
    message(FATAL_ERROR "wiringPi library not found!")  
endif()  

include_directories(src)
add_library(Arknights 
    src/Arknights/Arknights.cpp
)

# add_executable(light  
#     src/LED/LEDController.cpp  
#     src/main.cpp  
# )  

add_executable(lightWithLogo
    src/light.cpp
)

# target_link_libraries(light ${WIRINGPI_LIB})  
target_link_libraries(lightWithLogo ${WIRINGPI_LIB} Arknights)
