#include "./BBTonboSession.h"

#include <iostream>


BBTonboSession::BBTonboSession() : m_running(false) {
    m_audioWorker = new BBTonboAudioWorker();
    m_queue = new ThreadSafeQueue<AudioData>();
    startSession();
}

BBTonboSession::~BBTonboSession() {
    stopSession();
}

void BBTonboSession::send(const AudioData& audioData) {
    m_queue->push(audioData);
}

void BBTonboSession::startSession() {
    if (!m_running) {
        m_running = true;
        m_sessionThread = std::thread(&BBTonboSession::run, this);
    }
}

void BBTonboSession::stopSession() {
    if (m_running) {
        m_running = false;

        if (m_sessionThread.joinable()) {
            m_sessionThread.join();
        }
    }
}

void BBTonboSession::run() {
    while (m_running) {
        AudioData audioData;
        m_queue->waitAndPop(audioData);
        // std::cout << audioData.buffer.size() << std::endl;
    }
}

