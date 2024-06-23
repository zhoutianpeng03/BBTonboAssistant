#include "BBTonboAssistantWindow.h"
#include "BBTonboAssistantController.h"
#include "BBTonboContext.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    // import qss

    // import tanscript file

    QApplication a(argc, argv);


    // initialization ui
    BBTonboContext* context = new BBTonboContext();
    BBTonboAssistantWindow* window = new BBTonboAssistantWindow();
    BBTonboAssistantController* controller = new BBTonboAssistantController(context, window);
    controller->initialization();
    return a.exec();
}
