#include "tst_scannerwidget.h"

// Don't change anything in the constructor or QTest will crash
tst_scannerWidget::tst_scannerWidget()
{

}

// Set up the common arrange
void tst_scannerWidget::initTestCase()
{
    scanner = new ScannerWidget;
}

// Test if the method prepare() create a Puzzle directory
void tst_scannerWidget::prepareTest()
{
    QString path = "../Images/Puzzle--3";

    scanner->prepare(-3, "test");

    QDir directory(path);
    bool exist = directory.exists();
    QVERIFY(exist);

    if (exist)
    {
        directory.removeRecursively();
    }

}
