#pragma once

#include <thread>

#include "BBTonboAudioWorker.h"

class BBTonboSession {
public:
    BBTonboSession();
    ~BBTonboSession();

    void send();

private:
    void startSession();
    void stopSession();
    void run();


private:
    std::thread m_sessionThread;
    bool m_running;
    BBTonboAudioWorker* m_audioWorker = nullptr;
};
