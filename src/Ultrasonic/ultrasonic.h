/**
 * @file LEDController.h
 * @brief Defines the LED class and associated functionality.
 */

#ifndef HCSR04_H
#define HCSR04_H

#pragma once

#include <iostream>
#include <iomanip>
#include <gpiod.h>
#include <thread>
#include <chrono>
#include <functional>

#include "ultrasonicDataTypes.h"


class hcsr04 {
private:
	struct gpiod_line* trigLine_;
	struct gpiod_line* echoLine_;
	int measureInterval_;
	bool isActive_;
	const char* chipName = "gpiochip0";
	std::thread workerThread_;

	void initializeGPIO();

	void dataCollection();

	void dataCalculation();

public:

	hcsr04();
	~hcsr04();

	using PulseCallback = std::function<void(const EchoPulse&)>;

	void startRanging(PulseCallback cb);

	void stopRanging();

	void setMeasureInterval(int interval);

	timespec microsToTimespec(int64_t micros);

private:
	PulseCallback pulseCallback_;
	
};

#endif