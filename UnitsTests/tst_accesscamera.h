#ifndef TST_ACCESSCAMERA_H
#define TST_ACCESSCAMERA_H
#include <QtTest>
#include "cameraWidget.h"


class AccessCamera : public QObject
{
    Q_OBJECT

public:
    AccessCamera();
    ~AccessCamera();

// Declaration of the Tests
private slots:
    // Specials QT Tests at the launch at the start and the end of the Test Case
    void initTestCase(); // start
    // Unit-Tests of Methods
    //void prepareTest();

private:
    CameraWidget* camera;

};
#endif // TST_ACCESSCAMERA_H
