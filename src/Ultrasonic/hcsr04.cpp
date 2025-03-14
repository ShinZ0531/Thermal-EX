#include "hcsr04.h"

hcsr04::hcsr04(){}

hcsr04::~hcsr04(){}

void hcsr04::init() {
	if (-1 == wiringPiSetup())
	{
		cerr << "setup error\n";
		exit(-1);
	}
	pinMode(trig, OUTPUT);
	pinMode(echo, INPUT);
}

void hcsr04::loop() {
	init();
	while (true)
	{
		implement();
		delay(2000);
	}
}

void hcsr04::implement() {
	// send data, 10us
	digitalWrite(trig, HIGH);
	// receive s (not us)
	delay(0.00001);
	// stop
	digitalWrite(trig, LOW);
	// define start and end time
	int64_t start, ends;

	// wait for the start of signal
	while (digitalRead(echo) == 0){}

	// start to keep time
	start = TimeUtils::getSysTimeMicros();

	// wait for the end of signal
	while (digitalRead(echo) == 1){}
	// stop to keep time
	ends = TimeUtils::getSysTimeMicros();

	// time gap
	long duration = ends - start;

	double wholeTime, halfTime;

	wholeTime = duration / 1000.0;
	cout << "Whole Time: " << fixed << setprecision(2) << wholeTime << "ms\t";

	double distance = duration / 2.0;
	halfTime = distance / 1000.0;
	cout << "Half time: " << fixed << setprecision(2) << halfTime << "ms\t";

	distance = distance * 343.0;

	cout << "Estimated distance: ";

	distance = distance / 1000.0;
	distance = distance / 10.0;
	cout << fixed << setprecision(2) << distance << "cm" << endl;

	distance = distance / 100.0;
}
