#include "tst_masterwidget.h"

// don't change anything in the constructor or it will crash
tst_masterWidget::tst_masterWidget()
{

}

// don't change anything in the destructor or it will crash
tst_masterWidget::~tst_masterWidget()
{

}

//set up the common arrange
void tst_masterWidget::initTestCase()
{

    master = new MasterWidget;
    QVERIFY(master->testDuTest());
}

/*
//clean up the common arrange but don't use delete or it will crash
void tst_masterWidget::cleanupTestCase()
{
}
*/

void tst_masterWidget::goToWebcamTest()
{
    master->goToWebcam();

    QCOMPARE(master->getLoadedPage(), MasterWidget::camera);
}

void tst_masterWidget::goToSavePuzzle()
{
    master->goToSavePuzzle();

    QCOMPARE(master->getLoadedPage(), MasterWidget::savePuzzle);
}
