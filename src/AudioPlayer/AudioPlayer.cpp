#include "AudioPlayer.h"
#include <alsa/asoundlib.h>
#include <fstream>
#include <iostream>
#include <cstring>

AudioPlayer::AudioPlayer(const std::string& device)
    : deviceName(device), playing(false) {}

AudioPlayer::~AudioPlayer() {
    stop();
}

bool AudioPlayer::playWav(const std::string& filepath, bool async) {
    if (playing) return false;
    playing = true;

    if (async) {
        playThread = std::thread(&AudioPlayer::playTask, this, filepath);
    } else {
        playTask(filepath);
    }
    return true;
}

void AudioPlayer::stop() {
    if (playing) {
        playing = false;
        if (playThread.joinable()) {
            playThread.join();
        }
    }
}

bool AudioPlayer::isPlaying() const {
    return playing;
}

void AudioPlayer::playTask(const std::string& filepath) {
    snd_pcm_t* pcmHandle;
    snd_pcm_hw_params_t* params;
    unsigned int rate = 44100;
    int channels = 1;
    snd_pcm_uframes_t frames = 32;

    // 打开音频设备
    if (snd_pcm_open(&pcmHandle, deviceName.c_str(), SND_PCM_STREAM_PLAYBACK, 0) < 0) {
        std::cerr << "[AudioPlayer] Error opening PCM device " << deviceName << "\n";
        playing = false;
        return;
    }

    // 分配参数结构
    snd_pcm_hw_params_malloc(&params);
    snd_pcm_hw_params_any(pcmHandle, params);
    snd_pcm_hw_params_set_access(pcmHandle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(pcmHandle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(pcmHandle, params, channels);
    snd_pcm_hw_params_set_rate_near(pcmHandle, params, &rate, 0);
    snd_pcm_hw_params_set_period_size_near(pcmHandle, params, &frames, 0);
    snd_pcm_hw_params(pcmHandle, params);
    snd_pcm_hw_params_free(params);
    snd_pcm_prepare(pcmHandle);

    // 打开 WAV 文件，跳过 44 字节头部
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        std::cerr << "[AudioPlayer] Failed to open file: " << filepath << "\n";
        snd_pcm_close(pcmHandle);
        playing = false;
        return;
    }
    file.seekg(44); // 跳过 WAV 头

    // 播放数据
    char buffer[4096];
    while (playing && file.read(buffer, sizeof(buffer))) {
        int framesRead = file.gcount() / 2; // 16bit = 2 bytes
        int err = snd_pcm_writei(pcmHandle, buffer, framesRead);
        if (err < 0) snd_pcm_prepare(pcmHandle); // underrun
    }

    file.close();
    snd_pcm_drain(pcmHandle);
    snd_pcm_close(pcmHandle);
    playing = false;
}
