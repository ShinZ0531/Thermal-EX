#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <string>
#include <thread>
#include <atomic>
#include <mutex>

class AudioPlayer {
public:
    AudioPlayer(const std::string& device = "plughw:2,0");
    ~AudioPlayer();

    bool playWav(const std::string& filepath, bool async = false);
    void stop();
    bool isPlaying() const;

private:
    std::string deviceName;
    std::atomic<bool> playing;
    std::thread playThread;
    std::mutex mtx;

    void playTask(const std::string& filepath);
};

#endif // AUDIOPLAYER_H
