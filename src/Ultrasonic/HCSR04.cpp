#include "HCSR04.h"
#include "Config.h"

HCSR04::HCSR04() : isActive_(false) {
	initializeGPIO();
}

HCSR04::~HCSR04() {
	stopRanging();
}


void HCSR04::initializeGPIO() {
	// open GPIO chip
    struct gpiod_chip* chip = gpiod_chip_open_by_name(chipName);
    if (!chip) {
        throw std::runtime_error("[Ultrasonic] Failed to open GPIO chip");
    }

    // get GPIO line ULTRASONIC_TRIG_BCM_PIN
    trigLine_ = gpiod_chip_get_line(chip, ULTRASONIC_TRIG_BCM_PIN);
    if (!trigLine_) {
        gpiod_chip_close(chip);
		std::ostringstream trigOss;
		trigOss << "[Ultrasonic][TRIG] Failed to get GPIO line" << ULTRASONIC_TRIG_BCM_PIN;
		throw std::runtime_error(trigOss.str());
    }

    // set output mode
    if (gpiod_line_request_output(trigLine_, "UltrasonicTrig", 0) < 0) {
        gpiod_chip_close(chip);
        throw std::runtime_error("[Ultrasonic][TRIG] Failed to set output mode");
    }

	// get GPIO line ULTRASONIC_ECHO_BCM_PIN
    echoLine_ = gpiod_chip_get_line(chip, ULTRASONIC_ECHO_BCM_PIN);
    if (!echoLine_) {
        gpiod_chip_close(chip);
        std::ostringstream echoOss;
		echoOss << "[Ultrasonic][ECHO] Failed to get GPIO line" << ULTRASONIC_TRIG_BCM_PIN;
		throw std::runtime_error(echoOss.str());
    }

    // set output mode
    if (gpiod_line_request_both_edges_events(echoLine_, "UltrasonicEcho") < 0) {
        gpiod_chip_close(chip);
        throw std::runtime_error("[Ultrasonic][ECHO] Failed to set both edges mode");
    }

	setMeasureInterval(MEASURE_INTERVAL);
}

void HCSR04::startRanging() {
    isActive_ = true;
	workerThread_ = std::thread(&HCSR04::dataCollection, this);
    // workerThread_ = std::thread([this](){ dataCollection(); });
}

void HCSR04::dataCollection() {
	while(isActive_){
		// used to store the data
		EchoPulse pulse;
		// int64_t start, ends;

		// send data, wait about measureInterval_, stop
		gpiod_line_set_value(trigLine_, 1);
		std::this_thread::sleep_for(std::chrono::microseconds(measureInterval_));
		gpiod_line_set_value(trigLine_, 0);

		timespec timeout = microsToTimespec(MAX_RESPONSE_TIME);

		// wait for rising edge
		int waitingSignal = gpiod_line_event_wait(echoLine_, &timeout);
		if (waitingSignal == 1) { // 事件发生
			gpiod_line_event event;
			gpiod_line_event_read(echoLine_, &event); // 读取事件类型
			if (event.event_type == GPIOD_LINE_EVENT_RISING_EDGE) {
				pulse.risingEdge = std::chrono::high_resolution_clock::now();
			}
			else{
				std::cerr << "[Ultrasonic] Error, expect rising edge, actual event is " << event.event_type << std::endl;
        		return;
			}
		}
		else{
			if (waitingSignal == 0) throw std::runtime_error("[Ultrasonic] Timeout for waiting rising edge");
			else throw std::runtime_error("[Ultrasonic] Error occurred while waiting for a rising edge");
		}

		// wait for falling edge
		waitingSignal = gpiod_line_event_wait(echoLine_, &timeout);
		if (waitingSignal == 1) {
			gpiod_line_event event;
			gpiod_line_event_read(echoLine_, &event);
			if (event.event_type == GPIOD_LINE_EVENT_FALLING_EDGE) {
				pulse.fallingEdge = std::chrono::high_resolution_clock::now();
			}
			else {
				std::cerr << "[Ultrasonic] Error, expect falling edge, actual event is " << event.event_type << std::endl;
        		return;
			}
		}
		else {
			if (waitingSignal == 0) throw std::runtime_error("[Ultrasonic] Timeout for waiting falling edge");
			else throw std::runtime_error("[Ultrasonic] Error occurred while waiting for a falling edge");
		}

		for(auto &cb: hcsr04CallbackInterfaces) {
			cb->hasHCSR04Sample(pulse);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(MEASURE_INTERVAL));
	}
}


void HCSR04::stopRanging() {
	if(!isActive_) return;
	isActive_ = false;
	// wait for the worker thread to finish
    if (workerThread_.joinable()) workerThread_.join();
	// release GPIO lines
	if (trigLine_ || echoLine_) {
		if (trigLine_) gpiod_line_release(trigLine_);
		if (echoLine_) gpiod_line_release(echoLine_);
        gpiod_chip_close(gpiod_line_get_chip(trigLine_));
    }
}

void HCSR04::setMeasureInterval(int interval) {
    if (interval > 0) measureInterval_ = interval;
	else throw std::runtime_error("[Ultrasonic] Failed to set measure interval. It must be positive number");
}

timespec HCSR04::microsToTimespec(int64_t micros) {
    timespec ts;
    ts.tv_sec = micros / 1'000'000;
    ts.tv_nsec = (micros % 1'000'000) * 1000;
    return ts;
}