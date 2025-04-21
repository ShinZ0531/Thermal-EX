// #pragma once
#include "KeyboardInputMonitor.h"


KeyboardInputMonitor::KeyboardInputMonitor()  : exitRequested(false), monitoring(false) {}

KeyboardInputMonitor::~KeyboardInputMonitor() {
        stopKeyboardInput();
}


void KeyboardInputMonitor::startKeyboardInput() {
    if (!monitoring.exchange(true)) {
        exitRequested.store(false);
        monitorThread = std::thread(&KeyboardInputMonitor::monitorInput, this);
        monitoring.store(true);
    }
}

void KeyboardInputMonitor::stopKeyboardInput() {
    if (monitoring.exchange(false)) {
        exitRequested.store(true);
        cv.notify_all();
        if (monitorThread.joinable()) monitorThread.join();
    }
}


bool KeyboardInputMonitor::isExitRequested() {
    return exitRequested.load();
}

void KeyboardInputMonitor::monitorInputSimple() {
    while (!exitRequested.load()) {
        char input;
        if (std::cin >> input) {
            const char lower_input = std::tolower(input);
            
            for (auto& cb : keyboardCallbackInterfaces) {
                cb->hasKeyboardSample(lower_input);
            }

            if (lower_input == 'q') {
                exitRequested.store(true);
            }
        } else {

            if (std::cin.eof()) {
                std::cout << "Input stream closed." << std::endl;
            } else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            exitRequested.store(true);
        }
    }
}

void KeyboardInputMonitor::monitorInput() {
    while (!exitRequested.load()) {
        char input;
        {
            std::unique_lock<std::mutex> lk(buffer_mtx);
            cv.wait_for(lk, std::chrono::milliseconds(100), [this]{
                return exitRequested.load() || std::cin.peek() != EOF;
            });

            if (exitRequested) break;

            if (!(std::cin >> input)) {
                if (std::cin.eof()) {
                    std::cerr << "Input stream closed" << std::endl;
                    exitRequested.store(true);
                    break;
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        }

        const char lower_input = std::tolower(input);
        
        {
            std::lock_guard<std::mutex> cb_lock(mtx);
            for (auto& cb : keyboardCallbackInterfaces) {
                if (cb) cb->hasKeyboardSample(lower_input);
            }
        }

        if (lower_input == 'q') {
            exitRequested.store(true);
            cv.notify_one();
        }
    }
    monitoring.store(false);
}

void KeyboardInputMonitor::setIsWorkningTrue() {
    isWorking.store(true);
}

void KeyboardInputMonitor::setIsWorkningFalse() {
    isWorking.store(false);
}

bool KeyboardInputMonitor::getIsWorking() {
    return isWorking.load();
}