#include "tst_accesscamera.h"

// don't change anything in the constructor or it will crash
AccessCamera::AccessCamera()
{

}

// don't change anything in the destructor or it will crash
AccessCamera::~AccessCamera()
{

}

//set up the common arrange
void AccessCamera::initTestCase()
{
    camera = new CameraWidget;
}


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



