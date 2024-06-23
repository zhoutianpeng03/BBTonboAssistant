#pragma once

#include <QObject>
#include "BBTonboAssistantWindow.h"
#include "BBTonboContext.h"
#include "util/BBTonboAudioInputHelper.h"

class BBTonboAssistantController: public QObject {
Q_OBJECT

public:
    BBTonboAssistantController(BBTonboContext* context, BBTonboAssistantWindow* window);
    ~BBTonboAssistantController();

    void initialization();

private slots:
    void processAudioData(const QByteArray &data);

private:
    BBTonboContext* m_context = nullptr;
    BBTonboAssistantWindow* m_window = nullptr;
    BBTonboAudioInputHelper* m_audioInputHelper = nullptr;
};
