cmake_minimum_required(VERSION 3.7.0)

project(Thermal-EX DESCRIPTION "LED blinking and ultrasonic ranging." VERSION 2.1.0 LANGUAGES CXX)

configure_file(${CMAKE_SOURCE_DIR}/src/Arknights/config.h.in ${CMAKE_SOURCE_DIR}/src/Arknights/config.h @ONLY)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -pedantic)

find_package(PkgConfig REQUIRED)  
pkg_check_modules(GPIOD REQUIRED libgpiod)  


add_library(Arknights 
    src/Arknights/Arknights.cpp
)

add_library(LEDController STATIC
    src/LED/LEDController.cpp
)

target_link_libraries(LEDController PRIVATE ${GPIOD_LIBRARIES})  

add_executable(light  
    src/main.cpp  
)

add_executable(Ultrasonic
	src/ultrasonic.cpp
    src/Ultrasonic/ultrasonic.cpp
    src/Ultrasonic/DataLogger.cpp
)



target_link_libraries(light PRIVATE 
    ${WIRINGPI_LIB} 
    Arknights 
    LEDController
    ${LIBGPIOD_LIBRARIES}
)  

target_link_libraries(Ultrasonic PRIVATE 
    ${GPIOD_LIBRARIES}
)

target_include_directories(light PRIVATE
    ${LIBGPIOD_INCLUDE_DIRS}
)

target_include_directories(Ultrasonic PRIVATE
    ${GPIOD_INCLUDE_DIRS}
    src
)

target_include_directories(Arknights PRIVATE src)
target_include_directories(LEDController PRIVATE src ${GPIOD_INCLUDE_DIRS})

