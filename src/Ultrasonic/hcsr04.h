#pragma once
#include <iostream>
#include <wiringPi.h>   
#include <iomanip>
#include "TimeUtils.h"
#include <gpiod.h>

const int trig = 28;
const int echo = 29;

using namespace std;

class hcsr04
{
public:
	hcsr04();
	~hcsr04();
public:

	void initializeGPIO();

	void static init();

	void static loop();

	void static implement();
};
