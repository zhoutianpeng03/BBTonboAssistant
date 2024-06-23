#include "./BBTonboAssistantController.h"

BBTonboAssistantController::BBTonboAssistantController(BBTonboContext* context, BBTonboAssistantWindow* window) {
    m_context = context;
    m_window = window;

    m_audioInputHelper = new BBTonboAudioInputHelper();
}

BBTonboAssistantController::~BBTonboAssistantController() {
    if (m_audioInputHelper) {
        m_audioInputHelper->stopRecording();
        delete m_audioInputHelper;
        m_audioInputHelper = nullptr;
    }
}

void BBTonboAssistantController::processAudioData(const QByteArray &data) {

}

void BBTonboAssistantController::initialization() {
    connect(m_audioInputHelper, &BBTonboAudioInputHelper::audioDataAvailable, this, &BBTonboAssistantController::processAudioData);

    m_audioInputHelper->startRecording();
    m_window->show();
}
