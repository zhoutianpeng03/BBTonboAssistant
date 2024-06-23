#include "./BBTonboAudioInputHelper.h"
#include <QMediaDevices>

BBTonboAudioInputHelper::BBTonboAudioInputHelper(QObject *parent)
    : QObject(parent), audioInput(nullptr), audioDevice(nullptr) {
    initializeAudioFormat();
    QAudioDevice defaultDeviceInfo(QMediaDevices::defaultAudioInput());
    if (!defaultDeviceInfo.isFormatSupported(format)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }

    audioInput = new QAudioSource(defaultDeviceInfo, format, this);
    audioInput->setBufferSize(4096);
}

BBTonboAudioInputHelper::~BBTonboAudioInputHelper() {
    stopRecording();
    delete audioInput;
}


void BBTonboAudioInputHelper::initializeAudioFormat() {
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);
}

void BBTonboAudioInputHelper::listAudioInputDevices() {
    const QList<QAudioDevice> devices = QMediaDevices::audioInputs();
    for (const QAudioDevice &deviceInfo : devices) {
        qDebug() << "Device Name:" << deviceInfo.description();
        qDebug() << "Sample Rate:" << deviceInfo.preferredFormat().sampleRate();
        qDebug() << "Channel Count:" << deviceInfo.preferredFormat().channelCount();
    }
}

void BBTonboAudioInputHelper::startRecording() {
    if (audioInput) {
        audioDevice = audioInput->start();
        if (!audioDevice) {
            qWarning() << "Failed to start audio device. State:" << audioInput->error();
            return;
        }
        connect(audioDevice, &QIODevice::readyRead, this, &BBTonboAudioInputHelper::handleReadyRead);
    }
}

void BBTonboAudioInputHelper::stopRecording() {
    if (audioInput) {
        audioInput->stop();
        disconnect(audioDevice, &QIODevice::readyRead, this, &BBTonboAudioInputHelper::handleReadyRead);
        audioDevice = nullptr;
    }
}

void BBTonboAudioInputHelper::handleReadyRead() {
    if (!audioDevice) return;

    QByteArray soundData = audioDevice->readAll();
    emit audioDataAvailable(soundData);
    // qDebug() << "Audio data size:" << soundData.size();
}
