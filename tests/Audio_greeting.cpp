#include "AudioPlayer/AudioPlayer.h"
#include <iostream>

/**
 * @brief Entry point for the application.
 * 
 * @return Integer 0 upon exit success, non-zero on error.
 */

 int main() {
    AudioPlayer player("plughw:2,0");
    player.playWav("../ThermalExVoice/Greeting.wav", false);
    return 0;
}
