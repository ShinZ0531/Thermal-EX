#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>
#include <iostream>

class AudioPlayer {
public:
    struct AudioPlayerCallbackInterface {
        virtual void hasAudioPlayerSample(int pulse) = 0;
    };

    AudioPlayer();
    ~AudioPlayer();

    bool playWav(const std::string& filepath, bool async = false);
    void stopAudio();
    bool isPlaying() const;

    void setOnFinishCallback(void(*callback)());

    void recognizeSpeech();

    void registerCallback(AudioPlayerCallbackInterface* ci) {
		audioplayerCallbackInterfaces.push_back(ci);
	}

private:
    std::vector<AudioPlayerCallbackInterface*> audioplayerCallbackInterfaces;
    std::atomic<bool> playing;
    std::thread playerThread;
    std::mutex mtx;


    void playTask(const std::string& filepath);
    void triggerCallbacks(int pulse);
};

#endif // AUDIOPLAYER_H