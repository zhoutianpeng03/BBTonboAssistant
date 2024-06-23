#pragma once

#include "BBTonboAssistantWindow.h"

#include <QVBoxLayout>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QEasingCurve>

BBTonboAssistantWindow::BBTonboAssistantWindow(QWidget *parent): QMainWindow(parent)
{
    setMinimumSize(800, 600);

    layoutView();
}

BBTonboAssistantWindow::~BBTonboAssistantWindow() {

}

void BBTonboAssistantWindow::switchToBackgroundMode(bool background) {
    if (background) {
        normalSize = size();
        normalPosition = pos();

        setFixedSize(300, 120);
        move(10, 10);

        setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
        show();
    } else {
        setFixedSize(normalSize);
        move(normalPosition);

        setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint);
        show();
    }
}

void BBTonboAssistantWindow::layoutView() {

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);


    lottieWidget = new QLabel(centralWidget);
    lottieWidget->setFixedWidth(280);
    lottieWidget->setFixedHeight(280);


    QPixmap pixmap(":/image/res/him.png");
    QSize labelSize = lottieWidget->size();
    QPixmap scaledPixmap = pixmap.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    lottieWidget->setPixmap(scaledPixmap);
    statusLabel = new QLabel("Status", centralWidget);
    transcriptLabel = new QLabel("Recognition Result", centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    layout->addSpacing(30);


    layout->addWidget(lottieWidget, 0, Qt::AlignHCenter);
    layout->addSpacing(50);
    layout->addWidget(statusLabel, 0, Qt::AlignHCenter);

    layout->addStretch();

    layout->addWidget(transcriptLabel, 0, Qt::AlignHCenter);
    layout->addSpacing(10);
    centralWidget->setLayout(layout);
}


