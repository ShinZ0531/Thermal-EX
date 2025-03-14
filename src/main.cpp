#include "LEDController.h"
#include "Arknights.h"
#include <iostream>  

int main() {  

    Arknights::printLogo();
    try {  
        LEDController led(17);  // 控制GPIO17的LED  
        led.startBlinking();    // 开始闪烁（默认500ms间隔）  
    } catch (const std::exception& e) {  
        std::cerr << "Error: " << e.what() << std::endl;  
    }  
    return 0;  
}  