#include <QApplication>
#include "tst_accesscamera.h"
#include "tst_masterwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    tst_masterWidget testMaster;
    QTest::qExec(&testMaster, argc, argv);

    AccessCamera testCamera;
    QTest::qExec(&testCamera, argc, argv);
    return 0;
}
