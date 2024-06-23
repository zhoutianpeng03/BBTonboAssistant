#pragma once

#include <vector>
#include <cstdint>

class AudioConverter {
public:
    static std::vector<float> ConvertPcm16ToFloat(const std::vector<int16_t>& pcmData) {
        std::vector<float> floatData(pcmData.size());
        const float scale = 1.0f / 32768.0f;
        for (size_t i = 0; i < pcmData.size(); ++i) {
            floatData[i] = pcmData[i] * scale;
        }
        return floatData;
    }

    static std::vector<float> ConvertPcm16ToFloat(const uint8_t* bytes, size_t length) {
        size_t numSamples = length / sizeof(int16_t);
        std::vector<float> floatData(numSamples);
        const float scale = 1.0f / 32768.0f;
        auto* pcmData = reinterpret_cast<const int16_t*>(bytes);
        for (size_t i = 0; i < numSamples; ++i) {
            floatData[i] = pcmData[i] * scale;
        }
        return floatData;
    }
};
