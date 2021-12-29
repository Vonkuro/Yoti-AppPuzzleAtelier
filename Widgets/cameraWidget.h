#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QtMultimediaWidgets>
#include <unistd.h>
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
    QPushButton* photoButton;

//objects managers of webcam
    QCamera* webcam;
    QCameraViewfinder* webcamViewfinder;
    QCameraImageCapture* webcamImageCapture;
    QCameraViewfinderSettings viewfinderSettings;

// attributs
    int puzzleId;
    int lastImageId;
    QString pathImageDirectory;
//methods controll of webcam
    bool checkWebcamAvailable();
    void webcamView();
// methods
    void newDir(QString dirPath);

private slots:
    void takePhoto();

};

#endif // CAMERAWIDGET_H
