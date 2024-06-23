#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "sherpa-onnx/c-api/c-api.h"


struct AsrConfig {
    std::string tokens;
    std::string encoder;
    std::string decoder;
    std::string joiner;
    int numThreads;
    std::string provider;
    std::string decodingMethod;
};


class BBTonboAsr {
public:
    BBTonboAsr(const AsrConfig& config) {
        SherpaOnnxOnlineRecognizerConfig recognizerConfig;
        memset(&recognizerConfig, 0, sizeof(recognizerConfig));

        recognizerConfig.model_config.tokens = config.tokens.c_str();
        recognizerConfig.model_config.transducer.encoder = config.encoder.c_str();
        recognizerConfig.model_config.transducer.decoder = config.decoder.c_str();
        recognizerConfig.model_config.transducer.joiner = config.joiner.c_str();
        recognizerConfig.model_config.num_threads = config.numThreads;
        recognizerConfig.model_config.provider = config.provider.c_str();
        recognizerConfig.decoding_method = config.decodingMethod.c_str();

        recognizer = CreateOnlineRecognizer(&recognizerConfig);
        if (!recognizer) {
            throw std::runtime_error("Failed to create online recognizer.");
        }
        stream = CreateOnlineStream(recognizer);
        if (!stream) {
            DestroyOnlineRecognizer(recognizer);
            throw std::runtime_error("Failed to create online stream.");
        }
    }

    ~BBTonboAsr() {
        // Clean up the recognizer and stream.
        if (stream) {
            DestroyOnlineStream(stream);
        }
        if (recognizer) {
            DestroyOnlineRecognizer(recognizer);
        }
    }

    std::string processAudio(const std::vector<float>& audioData) {
        AcceptWaveform(stream, 16000, audioData.data(), audioData.size());

        // Decode the stream.
        DecodeOnlineStream(recognizer, stream);
        const SherpaOnnxOnlineRecognizerResult* result = GetOnlineStreamResult(recognizer, stream);
        std::string text = result->text;
        DestroyOnlineRecognizerResult(result);

        return text;
    }

private:
    const SherpaOnnxOnlineRecognizer* recognizer;
    const SherpaOnnxOnlineStream* stream;
};

// Usage example:

int main() {
    // Configure the ASR model.
    AsrConfig config;
    config.tokens = "/path/to/tokens.txt";
    config.encoder = "/path/to/encoder.onnx";
    config.decoder = "/path/to/decoder.onnx";
    config.joiner = "/path/to/joiner.onnx";
    config.numThreads = 1;
    config.provider = "cpu";
    config.decodingMethod = "greedy_search";

    // Initialize the ASR processor.
    BBTonboAsr asrProcessor(config);

    // Prepare the audio data (example: read from a WAV file).
    std::vector<float> audioData = {};

    // Process the audio data and get the transcription.
    std::string transcription = asrProcessor.processAudio(audioData);

    // Output the transcription.
    std::cout << "Transcription: " << transcription << std::endl;

    return 0;
}
