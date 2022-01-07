#include "tst_masterwidget.h"

// Don't change anything in the constructor or QTest will crash
tst_masterWidget::tst_masterWidget()
{

}

// Don't change anything in the destructor or QTest will crash
tst_masterWidget::~tst_masterWidget()
{

}

// Set up the common arrange
void tst_masterWidget::initTestCase()
{

    master = new MasterWidget;
    QVERIFY(master->testDuTest());
}

/*
// Clean up the common arrange but don't use delete or QTest will crash
void tst_masterWidget::cleanupTestCase()
{
}
*/

// Test if the method goToWebcam display the camera widget
void tst_masterWidget::goToWebcamTest()
{
    master->goToWebcam();

    QCOMPARE(master->getLoadedPage(), MasterWidget::camera);
}

// Test if the method goToSavePuzzle display the save puzzle widget
void tst_masterWidget::goToSavePuzzleTest()
{
    master->goToSavePuzzle();

    QCOMPARE(master->getLoadedPage(), MasterWidget::savePuzzle);
}

// Test if the method goToScanner display the scanner widget
void tst_masterWidget::goToScannerTest()
{
    master->goToScanner();

    QCOMPARE(master->getLoadedPage(), MasterWidget::scanner);
}

