#include "masterWidget.h"
#include "cameraWidget.h"
#include "scannerWidget.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MasterWidget w;
    //w.show();
    //w.test();

    ScannerWidget s;
    s.prepareScanner();

    return a.exec();
}
