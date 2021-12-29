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
    explicit CameraWidget(int id, QWidget *parent = 0);
    ~CameraWidget();
    void test();
    void start();
    void stop();

private:
//object managers of view
    QVBoxLayout* cameraLayout;

//objects managers of webcam
    QCamera* webcam;
    QCameraViewfinder* webcamViewfinder;
    QCameraImageCapture* webcamImageCapture;
    QCameraViewfinderSettings viewfinderSettings;

// attributs
    int puzzleId;
//methods controll of webcam
    bool checkWebcamAvailable();
    void webcamView();

};

#endif // CAMERAWIDGET_H
