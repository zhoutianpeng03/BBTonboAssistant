#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QLabel>

class BBTonboAssistantWindow : public QMainWindow {
    Q_OBJECT
public:
    BBTonboAssistantWindow(QWidget *parent = nullptr);
    ~BBTonboAssistantWindow();

    void switchToBackgroundMode(bool background);
    void layoutView();

private:
    // TODO@ztp rename
    QSize normalSize;
    QPoint normalPosition;

    QWidget *centralWidget = nullptr;
    QLabel *lottieWidget = nullptr;
    QLabel *statusLabel = nullptr;
    QLabel *transcriptLabel = nullptr;
};
