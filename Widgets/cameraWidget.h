#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QtMultimediaWidgets>
#include "widgets_global.h"

class CameraWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraWidget(QWidget *parent = 0);
    ~CameraWidget();
    void test();

private:
//object managers of view
    QVBoxLayout* cameraLayout;

//objects managers of webcam
    QCamera* webcam;
    QCameraViewfinder* webcamViewfinder;
    QCameraImageCapture* webcamImageCapture;
    QCameraViewfinderSettings viewfinderSettings;

//methods controll of webcam
    bool checkWebcamAvailable();
    void webcamView();

};

#endif // CAMERAWIDGET_H
