 add_executable(LED_light  
    LED_light.cpp  
    # ${CONFIG_FILE}
)

add_executable(HCSR04_Printer
	HCSR04_Printer.cpp
    # src/Ultrasonic/HCSR04.cpp
    # ${CONFIG_FILE}
)

add_executable(SG90_move
    SG90_move.cpp
)

add_executable(DistanceWaring
    DistanceWaring.cpp
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

target_link_libraries(SG90_move PRIVATE 
    SG90
    # ${GPIOD_LIBRARIES}
)

target_link_libraries(DistanceWaring PRIVATE 
    HCSR04
    LED
    Keyboard
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

target_include_directories(SG90_move PRIVATE 
    ../src
    # ${GPIOD_INCLUDE_DIRS}
)

target_include_directories(DistanceWaring PRIVATE 
    ../src
    # ${GPIOD_INCLUDE_DIRS}
)

set_target_properties(LED_light PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

set_target_properties(HCSR04_Printer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

set_target_properties(SG90_move PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

set_target_properties(DistanceWaring PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)