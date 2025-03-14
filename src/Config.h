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
 * @def ULTRASONIC_TRIG_BCM_PIN
 * @brief BCM number of GPIO which is connected with the TRIG of ultrasonic.
 * @def ULTRASONIC_ECHO_BCM_PIN
 * @brief BCM number of GPIO which is connected with the ECHO of ultrasonic.
 */
#define ULTRASONIC_TRIG_BCM_PIN   20
#define ULTRASONIC_ECHO_BCM_PIN   21

/**
 * @def BLINK_INTERVAL
 * @brief Time gap between light on and off. (ms)
 */
#define BLINK_INTERVAL 100

#define SOUND_SPEED 0.0343  // sound speed
#define MAX_RESPONSE_TIME 100000   // max response time
#define MEASURE_INTERVAL 200      // measure interval of sensor
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