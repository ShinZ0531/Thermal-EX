/**
 * @file HCSR04.h
 * @brief Defines the HCSR04 class and associated functionality.
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


class HCSR04 {
public:

	HCSR04();
	~HCSR04();

	struct HCSR04CallbackInterface {
	    /**
	     * Called when a new sample is available.
	     * This needs to be implemented in a derived
	     * class by the client. Defined as abstract.
	     * \param sample rising edge time and falling edge time
	     **/
	virtual void hasHCSR04Sample(EchoPulse sample) = 0;
    };

	void registerCallback(HCSR04CallbackInterface* ci) {
		hcsr04CallbackInterfaces.push_back(ci);
	}

	void startRanging();
	void stopRanging();
	void setMeasureInterval(int interval);
	timespec microsToTimespec(int64_t micros);

private:
	std::vector<HCSR04CallbackInterface*> hcsr04CallbackInterfaces;

	struct gpiod_line* trigLine_;
	struct gpiod_line* echoLine_;

	int measureInterval_;
	bool isActive_;
	const char* chipName = "gpiochip0";
	std::thread workerThread_;

	void initializeGPIO();
	void dataCollection();
	void dataCalculation();
};

#endif