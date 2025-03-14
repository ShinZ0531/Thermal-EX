#include <iostream>
#include <unistd.h>
#include "ws2811.h"

#define LED_COUNT 16       // 总共16颗LED
#define LED_GPIO_PIN 18    // WS2812B数据输入引脚（GPIO18）
#define TARGET_FREQ WS2811_TARGET_FREQ
#define DMA 10

ws2811_t ledstring = {
    .freq = TARGET_FREQ,
    .dmanum = DMA,
    .channel = {
        [0] = {
            .gpionum = LED_GPIO_PIN,
            .count = LED_COUNT,
            .invert = 0,
            .brightness = 255,
            .strip_type = WS2811_STRIP_GRB, // 颜色格式：GRB
        },
    },
};

// 设置LED颜色
void set_led_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    if (index < LED_COUNT) {
        ledstring.channel[0].leds[index] = (r << 16) | (g << 8) | b;
    }
}

// 渲染并更新灯带
void update_leds() {
    ws2811_render(&ledstring);
}

int main() {
    if (ws2811_init(&ledstring) != WS2811_SUCCESS) {
        std::cerr << "WS2812B 初始化失败！" << std::endl;
        return -1;
    }

    // **白灯始终保持亮着**
    for (int i = 12; i < 16; i++) {
        set_led_color(i, 255, 255, 255);
    }

    update_leds();

    int delay_time = 500; // 初始闪烁间隔 500ms

    // **绿灯闪烁，逐渐加快**
    for (int step = 0; step < 10; step++) {
        // **点亮12个绿灯**
        for (int i = 0; i < 12; i++) {
            set_led_color(i, 0, 255, 0);
        }
        update_leds();
        usleep(delay_time * 1000);

        // **熄灭12个绿灯**
        for (int i = 0; i < 12; i++) {
            set_led_color(i, 0, 0, 0);
        }
        update_leds();
        usleep(delay_time * 1000);

        // **逐步加快**
        delay_time = (delay_time * 8) / 10; // 每次减少 20% 闪烁间隔
        if (delay_time < 50) delay_time = 50; // 最小间隔 50ms，防止过快
    }

    // **最终熄灭所有LED**
    for (int i = 0; i < LED_COUNT; i++) {
        set_led_color(i, 0, 0, 0);
    }
    update_leds();

    ws2811_fini(&ledstring);
    return 0;
}


