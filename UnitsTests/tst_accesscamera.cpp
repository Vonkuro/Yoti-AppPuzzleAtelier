#include "tst_accesscamera.h"

// Don't change anything in the constructor or QTest will crash
AccessCamera::AccessCamera()
{

}

// Don't change anything in the destructor or QTest will crash
AccessCamera::~AccessCamera()
{

}

// Set up the common arrange
void AccessCamera::initTestCase()
{
    camera = new CameraWidget;
}

// Test if the method prepare() create a Puzzle directory
void AccessCamera::prepareTest()
{
    QString path = "../Images/Puzzle--3";

    camera->prepare(-3);

    QDir directory(path);
    bool exist = directory.exists();
    QVERIFY(exist);

    if (exist)
    {
        directory.removeRecursively();
    }

}



