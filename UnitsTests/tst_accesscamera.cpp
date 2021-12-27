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

void AccessCamera::initTestCase()
{

}

void AccessCamera::cleanupTestCase()
{

}

void AccessCamera::test_case1()
{
//    QVERIFY(cameraLibrary::checkWebcamAvailable());
}

QTEST_APPLESS_MAIN(AccessCamera)

#include "tst_accesscamera.moc"
