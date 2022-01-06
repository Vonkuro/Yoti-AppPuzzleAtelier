#include "tst_scannerwidget.h"

tst_scannerWidget::tst_scannerWidget()
{

}

//set up the common arrange
void tst_scannerWidget::initTestCase()
{
    scanner = new ScannerWidget;
}


void tst_scannerWidget::prepareTest()
{
    QString path = "../Images/Puzzle--3";

    scanner->prepare(-3);

    QDir directory(path);
    bool exist = directory.exists();
    QVERIFY(exist);

    if (exist)
    {
        directory.removeRecursively();
    }

}
