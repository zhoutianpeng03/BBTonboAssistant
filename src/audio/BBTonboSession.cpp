#include "./BBTonboSession.h"


BBTonboSession::BBTonboSession() : m_running(false) {
    m_audioWorker = new BBTonboAudioWorker();
    startSession();
}

BBTonboSession::~BBTonboSession() {
    stopSession();
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
        // 执行循环的工作，比如处理音频数据

        // 你可以在这里添加一个 sleep 或 wait 来减少 CPU 的使用
        // std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
