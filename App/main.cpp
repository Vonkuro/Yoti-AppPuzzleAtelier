#include "masterWidget.h"
#include "cameraWidget.h"
#include "scannerWidget.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MasterWidget w;
    w.show();
    w.test();

    /*
     * Place where I write the main for testing purpose
    ScannerWidget s;
    s.init_v2();
    */
    return a.exec();
}
