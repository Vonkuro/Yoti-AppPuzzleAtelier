#ifndef TST_ACCESSCAMERA_H
#define TST_ACCESSCAMERA_H
#include <QtTest>
#include "cameraWidget.h"

// add necessary includes here

class AccessCamera : public QObject
{
    Q_OBJECT

public:
    AccessCamera();
    ~AccessCamera();

private slots:
    void initTestCase();
    void prepareTest();

private:
    CameraWidget* camera;

};
#endif // TST_ACCESSCAMERA_H
