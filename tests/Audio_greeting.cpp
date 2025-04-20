#include "AudioPlayer/AudioPlayer.h"
#include <iostream>

/**
 * @brief Entry point for the application.
 * 
 * @return Integer 0 upon exit success, non-zero on error.
 */

int main() {
    try {
        AudioPlayer audioPlayer;
        audioPlayer.playWav("ThermalExVoice/Greeting.wav", true);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}