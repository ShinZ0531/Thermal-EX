cmake_minimum_required(VERSION 3.7.0)

project(Thermal-EX DESCRIPTION "New function about ultrasonic." VERSION 1.3.0 LANGUAGES CXX)

configure_file(${CMAKE_SOURCE_DIR}/src/Arknights/config.h.in ${CMAKE_SOURCE_DIR}/src/Arknights/config.h @ONLY)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -pedantic)

find_package(PkgConfig REQUIRED)  
pkg_check_modules(GPIOD REQUIRED libgpiod)  

find_library(WIRINGPI_LIB wiringPi)  
if (NOT WIRINGPI_LIB)  
    message(FATAL_ERROR "wiringPi library not found!")  
endif()  

include_directories(src ${GPIOD_INCLUDE_DIRS})

add_library(Arknights 
    src/Arknights/Arknights.cpp
)

add_library(LEDController STATIC
    src/LED/LEDController.cpp
)

add_library(Ultrasonic STATIC
    src/Ultrasonic/Ultrasonic.cpp
)

add_library(hcsr04 src/Ultrasonic/hcsr04.cpp)
add_library(TimeUtils src/Ultrasonic/TimeUtils.cpp)

target_link_libraries(LEDController PRIVATE ${GPIOD_LIBRARIES})  

add_executable(light  
    src/main.cpp  
)

add_executable(ultrasonic src/ultrasonic.cpp)
add_executable(HCSR04
	src/HCSR04.cpp
)

target_link_libraries(ultrasonic PRIVATE
    Ultrasonic
    LEDController
    ${LIBGPIOD_LIBRARIES}
)

target_link_libraries(light PRIVATE 
    ${WIRINGPI_LIB} 
    Arknights 
    LEDController
    ${LIBGPIOD_LIBRARIES}
)  

target_link_libraries(HCSR04 PRIVATE
    hcsr04
    TimeUtils
    ${WIRINGPI_LIB}
)

target_include_directories(light PRIVATE
    ${LIBGPIOD_INCLUDE_DIRS}
)

target_include_directories(ultrasonic PRIVATE
    ${LIBGPIOD_INCLUDE_DIRS}
)