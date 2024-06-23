#include "./BBTonboAssistantController.h"
#include "./audio/BBTonboSession.h"
#include "./util/BBTonboAudioConverter.h"

BBTonboAssistantController::BBTonboAssistantController(BBTonboContext* context, BBTonboAssistantWindow* window) {
    m_context = context;
    m_window = window;
    m_audioInputHelper = new BBTonboAudioInputHelper();

    m_context->session = new BBTonboSession();

}

BBTonboAssistantController::~BBTonboAssistantController() {
    if (m_audioInputHelper) {
        m_audioInputHelper->stopRecording();
        delete m_audioInputHelper;
        m_audioInputHelper = nullptr;
    }
}


void BBTonboAssistantController::processAudioData(const QByteArray &data) {
    const int16_t *pcmData = reinterpret_cast<const int16_t *>(data.constData());
    std::vector<int16_t> pcmVector(pcmData, pcmData + data.size() / sizeof(int16_t));
    std::vector<float> floatData = AudioConverter::ConvertPcm16ToFloat(pcmVector);

    AudioData audioDataToSend;
    audioDataToSend.buffer = std::move(floatData);
    audioDataToSend.timestamp = std::chrono::steady_clock::now();
    // qDebug() << "processAudioData:" << data.length();

    m_context->session->send(audioDataToSend);
}

void BBTonboAssistantController::initialization() {
    connect(m_audioInputHelper, &BBTonboAudioInputHelper::audioDataAvailable, this, &BBTonboAssistantController::processAudioData);

    m_audioInputHelper->startRecording();
    m_window->show();
}
