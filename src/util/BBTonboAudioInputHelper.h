#pragma once

#include <QAudioSource>
#include <QAudioDevice>
#include <QAudioFormat>
#include <QIODevice>
#include <QByteArray>
#include <QDebug>

class QAudioSource;
class QIODevice;
class QByteArray;

/**
 * @brief Class responsible for handling audio input using Qt's multimedia framework.
 */
class BBTonboAudioInputHelper : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructs an audio input helper object.
     *
     * @param parent Parent for this QObject.
     */
    explicit BBTonboAudioInputHelper(QObject *parent = nullptr);

    /**
     * @brief Destroys the audio input helper object.
     */
    ~BBTonboAudioInputHelper();

    /**
     * @brief Initializes the audio input and starts recording.
     */
    void startRecording();

    /**
     * @brief Stops the audio recording and releases the audio input device.
     */
    void stopRecording();

    /**
     * @brief Lists all available audio input devices to the debug output.
     */
    void listAudioInputDevices();

signals:
    /**
     * @brief Signal emitted when new audio data is available.
     *
     * @param data The available audio data.
     */
    void audioDataAvailable(const QByteArray &data);

private slots:
    /**
     * @brief Slot to handle the readyRead signal from the audio device.
     *        Reads available audio data and emits the audioDataAvailable signal.
     */
    void handleReadyRead();

private:
    QAudioSource *audioInput; ///< Pointer to the audio source object.
    QIODevice *audioDevice;   ///< Pointer to the IO device for audio data.
    QAudioFormat format;      ///< Audio format used for recording.

    /**
     * @brief Initializes the audio format with default parameters.
     */
    void initializeAudioFormat();
};
