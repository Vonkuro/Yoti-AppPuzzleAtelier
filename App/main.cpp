#include "masterWidget.h"
#include "cameraWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CameraWidget w;
    w.show();
    w.test();

    return a.exec();
}
