#include "AudioPlayer.h"
#include <unistd.h>
#include <cstdio>
#include <cstdlib>


AudioPlayer::AudioPlayer() : playing(false) {}

AudioPlayer::~AudioPlayer() {
    stopAudio();
}

bool AudioPlayer::playWav(const std::string& filepath, bool async) {
    if (playing.load()) return false;

    playing.store(true);
    if (async) {
        playerThread = std::thread(&AudioPlayer::playTask, this, filepath);
    } else {
        playTask(filepath);
    }
    return true;
}

void AudioPlayer::playTask(const std::string& filepath) {
    std::lock_guard<std::mutex> lock(mtx);

    std::string command = "aplay \"" + filepath + "\"";
    int ret = std::system(command.c_str());

    triggerCallbacks(ret);
    playing.store(false);
}

void AudioPlayer::stopAudio() {
    if (playing.load()) {
        std::system("pkill -f aplay");
        playing.store(false);
        if (playerThread.joinable()) {
            playerThread.join();
        }
    }
}

bool AudioPlayer::isPlaying() const {
    return playing.load();
}

void AudioPlayer::setOnFinishCallback(void(*callback)()) {
}

void AudioPlayer::recognizeSpeech() {
    std::cout << "[Speech Recognition] 识别中...（此为占位函数）" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "[Speech Recognition] 假设识别出“打开灯”" << std::endl;

    triggerCallbacks(1); 
}

void AudioPlayer::triggerCallbacks(int pulse) {
    for (auto& cb : audioplayerCallbackInterfaces) {
        cb->hasAudioPlayerSample(pulse);
    }
}
