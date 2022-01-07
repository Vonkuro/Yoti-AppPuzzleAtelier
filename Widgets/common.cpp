#include "common.h"

// Create a directory if it doesn't exit
void newDir(QString dirPath)
{
    QDir dir(dirPath);
    QDir dir2;
    if(!dir.exists())
    {
        dir2.mkpath(dirPath);
    }
}

// Delay the widget loop for milliSeconds
void delay(int milliSeconds)
{
    QTime dieTime = QTime::currentTime().addMSecs(milliSeconds);

    while(QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
