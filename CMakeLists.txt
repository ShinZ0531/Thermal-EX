cmake_minimum_required(VERSION 3.7.0)

project(Thermal-EX DESCRIPTION "Ultrasonic-HCSR04, LED" VERSION 2.1.1 LANGUAGES CXX)

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

add_executable(HCSR04_Printer
	src/HCSR04_Printer.cpp
    src/UltrasonicCallback/HCSR04.cpp
    # src/UltrasonicCallback/DataLogger.cpp
)


target_link_libraries(light PRIVATE 
    ${WIRINGPI_LIB} 
    Arknights 
    LEDController
    ${LIBGPIOD_LIBRARIES}
)  

target_link_libraries(HCSR04_Printer PRIVATE 
    ${GPIOD_LIBRARIES}
)

target_include_directories(light PRIVATE
    ${LIBGPIOD_INCLUDE_DIRS}
)

target_include_directories(HCSR04_Printer PRIVATE
    ${GPIOD_INCLUDE_DIRS}
    src
)

target_include_directories(Arknights PRIVATE src)
target_include_directories(LEDController PRIVATE src ${GPIOD_INCLUDE_DIRS})

