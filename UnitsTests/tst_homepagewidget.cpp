#include "tst_homepagewidget.h"

tst_homepageWidget::tst_homepageWidget()
{

}

//set up the common arrange
void tst_homepageWidget::initTestCase()
{
    homepage = new HomepageWidget;
}

void tst_homepageWidget::startSignalTest()
{
    QSignalSpy spy(homepage, SIGNAL(startApp()));
    QTest::mouseClick(homepage->startButton, Qt::LeftButton);

    QCOMPARE(spy.count(), 1);

}
