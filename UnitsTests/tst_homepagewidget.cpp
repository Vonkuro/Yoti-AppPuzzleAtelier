#include "tst_homepagewidget.h"

// Don't change anything in the constructor or QTest will crash
tst_homepageWidget::tst_homepageWidget()
{

}

// Set up the common arrange
void tst_homepageWidget::initTestCase()
{
    homepage = new HomepageWidget;
}

// Test if the startButton emit the start signal
void tst_homepageWidget::startSignalTest()
{
    QSignalSpy spy(homepage, SIGNAL(startApp()));
    QTest::mouseClick(homepage->startButton, Qt::LeftButton);

    QCOMPARE(spy.count(), 1);

}
