#pragma once
#include <atomic>
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <condition_variable>

class KeyboardInputMonitor {
public:
    KeyboardInputMonitor();
    ~KeyboardInputMonitor();

    struct KeyboardCallbackInterface {
	    /**
	     * Called when a new sample is available.
	     * This needs to be implemented in a derived
	     * class by the client. Defined as abstract.
	     * \param sample rising edge time and falling edge time
	     **/
	virtual void hasKeyboardSample(char key) = 0;
    };

    void registerCallback(KeyboardCallbackInterface* ci) {
		keyboardCallbackInterfaces.push_back(ci);
	}

    void startKeyboardInput();
    void stopKeyboardInput();

    bool isExitRequested();
    void setIsWorkningTrue();
    void setIsWorkningFalse();
    bool getIsWorking();

private:
    std::vector<KeyboardCallbackInterface*> keyboardCallbackInterfaces;

    void monitorInputSimple();
    void monitorInput();

    std::atomic<bool> exitRequested{false};
    std::atomic<bool> monitoring{false};
    std::atomic<bool> isWorking{false};
    std::mutex mtx;
    std::mutex buffer_mtx;
    std::thread monitorThread;
    std::condition_variable cv;
};

