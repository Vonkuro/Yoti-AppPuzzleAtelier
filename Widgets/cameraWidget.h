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
    explicit CameraWidget(QWidget *parent = 0);
    ~CameraWidget();
    void prepare(int id);
    void start();
    void stop();

signals:
    void photoTaken(int idPuzzle, int idImage);

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
    void delay();
    void viewStyle();


private slots:
    void takePhoto();


};

#endif // CAMERAWIDGET_H
