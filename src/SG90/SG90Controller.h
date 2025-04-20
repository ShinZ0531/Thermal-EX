#ifndef SG90_CONTROLLER_H
#define SG90_CONTROLLER_H

#include <gpiod.h>
#include <stdexcept>
#include <chrono>
#include <vector>
#include <atomic>
#include <thread>
#include <mutex>

#include "rpi_pwm.h"

enum class SG90Mode {
    SCANNING,
    TRACKING
};

class SG90Controller {
public:
    SG90Controller(int pwm_channel = 0, int pwm_chip = 0);
    ~SG90Controller();

    struct SG90CallbackInterface {
	    /**
	     * Called when a new sample is available.
	     * This needs to be implemented in a derived
	     * class by the client. Defined as abstract.
	     * \param sample rising edge time and falling edge time
	     **/
	virtual void hasSG90Sample(float sample) = 0;
    };
    
    void registerCallback(SG90CallbackInterface* ci) {
        sg90CallbackInterfaces.push_back(ci);
    }

    void setAngle(float angle);
    void setAngleSmooth(float angle);
    void setSpeed(float deg_per_sec);
    void change15Angle(float delta);

    void enableSG90();
    void disableSG90();

    int waitForKeyboardInput();
    int waitForKeyboardInputFixed();
    void notifyCallbacks(float targetangle);
    void startScanning();
    void stopScanning();
    void setMode(SG90Mode mode);

private:
    void pwmLoop();
    void updatePWM();
    int angleToPulse(int angle); 
    float angleToDuty(float angle) const;


    void scanningRoutine();
    void trackTarget(float relativeOffset);

    std::vector<SG90CallbackInterface*> sg90CallbackInterfaces;
    struct gpiod_line* servoLine;
    const char* chipName = "gpiochip0";

    

    RPI_PWM pwm;
    std::thread pwmThread; 
    std::mutex dataMutex;

    std::atomic<float> currentAngle;
    std::atomic<float> targetAngle; 
    std::atomic<float> moveSpeed;
    std::atomic<bool> isActive_;
    std::atomic<bool> smoothMode;
    std::mutex angleLock;
    std::atomic<SG90Mode> currentMode;
    std::thread scanThread;
    std::mutex modeMutex;
    bool stopScanThread = false;


    const float PWM_FREQ = 50.0f;
    const float MIN_PULSE = 500.0f;
    const float MAX_PULSE = 2400.0f;
};

#endif // SG90_CONTROLLER_H
