#pragma once

#include "./audio/BBTonboSession.h"

class BBTonboContext {
public:
    BBTonboContext();

    ~BBTonboContext();

    BBTonboSession* session = nullptr;

};
