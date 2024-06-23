#pragma once

#include <thread>
#include <vector>
#include <chrono>

#include "../base/ThreadSafeQueue.h"
#include "BBTonboAudioWorker.h"

struct AudioData {
    std::vector<float> buffer;
    std::chrono::steady_clock::time_point timestamp;
};

class BBTonboSession {
public:
    BBTonboSession();
    ~BBTonboSession();

    void send(const AudioData& audioData);

private:
    void startSession();
    void stopSession();
    void run();


private:
    std::thread m_sessionThread;
    bool m_running;
    ThreadSafeQueue<AudioData>* m_queue = nullptr;
    BBTonboAudioWorker* m_audioWorker = nullptr;
};
