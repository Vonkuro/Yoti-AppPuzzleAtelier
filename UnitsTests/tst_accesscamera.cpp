#include <QtTest>
//#include "../App/cameraLibrary.h"

// add necessary includes here

class AccessCamera : public QObject
{
    Q_OBJECT

public:
    AccessCamera();
    ~AccessCamera();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

AccessCamera::AccessCamera()
{

}

AccessCamera::~AccessCamera()
{

}

//set up the common arrange
void AccessCamera::initTestCase()
{

}

//clean up the common arrange
void AccessCamera::cleanupTestCase()
{

}

//first test, it will pass if the unit-test are correctly setup
void AccessCamera::test_case1()
{
//    QVERIFY(cameraLibrary::checkWebcamAvailable());
}

QTEST_APPLESS_MAIN(AccessCamera)

#include "tst_accesscamera.moc"
