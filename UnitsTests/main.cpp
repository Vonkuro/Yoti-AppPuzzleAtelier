#include <QApplication>
#include "tst_accesscamera.h"
#include "tst_masterwidget.h"
#include "tst_scannerwidget.h"
#include "tst_envlocal.h"
#include "tst_homepagewidget.h"
#include "tst_validationwidget.h"


// Launch the Unit-Tests class by class
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    tst_masterWidget testMaster;
    QTest::qExec(&testMaster, argc, argv);

    AccessCamera testCamera;
    QTest::qExec(&testCamera, argc, argv);

    tst_scannerWidget testScanner;
    QTest::qExec(&testScanner, argc, argv);

    tst_envLocal testEnvLocal;
    QTest::qExec(&testEnvLocal, argc, argv);

    tst_homepageWidget testHomepage;
    QTest::qExec(&testHomepage, argc, argv);

    tst_validationWidget testValidation;
    QTest::qExec(&testValidation, argc, argv);
    return 0;
}
