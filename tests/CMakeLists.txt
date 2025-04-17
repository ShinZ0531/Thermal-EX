 add_executable(LED_light  
    LED_light.cpp  
    # ${CONFIG_FILE}
)

add_executable(HCSR04_Printer
	HCSR04_Printer.cpp
    # src/Ultrasonic/HCSR04.cpp
    # ${CONFIG_FILE}
)


target_link_libraries(LED_light PRIVATE 
    Arknights 
    LED
    # ${GPIOD_LIBRARIES}
)  

target_link_libraries(HCSR04_Printer PRIVATE 
    HCSR04
    # ${GPIOD_LIBRARIES}
)


target_include_directories(HCSR04_Printer PRIVATE
    ../src
    # ${GPIOD_INCLUDE_DIRS}
)

target_include_directories(LED_light PRIVATE 
    ../src
    # ${GPIOD_INCLUDE_DIRS}
)

set_target_properties(LED_light PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

set_target_properties(HCSR04_Printer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)