/**
 * @file Config.h
 * @brief Hardware configuration for Thermal-Ex.
 */

#pragma once

/**
 * @def LED_BCM_PIN
 * @brief BCM number of GPIO which is connected with the LED light.
 */
#define LED_BCM_PIN 23


/**
 * @def BLINK_INTERVAL
 * @brief Time gap between light on and off. (ms)
 */
#define BLINK_INTERVAL 1000

/**
 * @def ULTRASONIC_TRIG_BCM_PIN
 * @brief BCM number of GPIO which is connected with the TRIG of ultrasonic.
 * @def ULTRASONIC_ECHO_BCM_PIN
 * @brief BCM number of GPIO which is connected with the ECHO of ultrasonic.
 */
#define ULTRASONIC_TRIG_BCM_PIN   20
#define ULTRASONIC_ECHO_BCM_PIN   21
// #define ULTRASONIC_ECHO_BCM_PIN   22




#define SOUND_SPEED 0.0343f  // sound speed
#define MAX_RESPONSE_TIME 100000   // max response time
#define MEASURE_INTERVAL 100     // measure interval of sensor. recommend 10
#define MAX_DISTANCE 200     // max distanve of ultrasonic
#define MIN_DISTANCE 20      // min distance of ultrasonic

/**
 * @def MAIN_LOOP_SLEEP_MS
 * @brief waiting gep of main
 */
#define MAIN_LOOP_SLEEP 50

/**
 * @def DISTANCE_TO_FREQ_RATIO
 * @brief ratio of transition from distance to blinking frequency (ms/cm)
 * @note formula: blink_interval_ms = distance_cm * DISTANCE_TO_FREQ_RATIO
 */
#define DISTANCE_TO_FREQ_RATIO  10

/**
 * @def SG90_BCM_PIN
 * @brief BCM number of GPIO which is connected with the SG90 servo motor.
 * @def SG90_PWM_CHANNEL
 * @brief PWM channel of the SG90 servo motor.
 * @def SG90_PWM_CHIP
 * @brief PWM chip of the SG90 servo motor.
 * @note PWM channel 0, chip 0 for GPIO12(pin32)
 */
#define SG90_BCM_PIN 18
#define SG90_PWM_CHANNEL 0
#define SG90_PWM_CHIP 0
#define SG90_PWM_FREQ 50.0f
#define SG90_PWM_MIN_PULSE 500.0f
#define SG90_PWM_MAX_PULSE 2400.0f
#define SG90_MAX_ANGLE 180.0f
#define SG90_MIN_ANGLE 0.0f
#define SG90_DEFAULT_ANGLE 90.0f
#define SG90_DEFAULT_SPEED 30.0f
#define SG90_UPDATE_INTERVAL 10ms

#define AUDIO_DEVICE "plughw:2,0"
#define AUDIO_FILE_PATH "../ThermalExVoice/"