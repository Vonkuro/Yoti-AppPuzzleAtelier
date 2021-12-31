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
// Tools for the Master Widget to Manage the Webcam
    void prepare(int id);
    void start();
    void stop();

// Taking the photo
signals:
    void photoTaken(int idPuzzle, int idImage);

private slots:
    void takePhoto();

private:
// object managers of view
    QVBoxLayout* cameraLayout;
    QPushButton* photoButton;

// objects managers of webcam
    QCamera* webcam;
    QCameraViewfinder* webcamViewfinder;
    QCameraImageCapture* webcamImageCapture;
    QCameraViewfinderSettings viewfinderSettings;

// attributs
    int puzzleId;
    int lastImageId;
    QString pathImageDirectory;
// methods to control and config the webcam
    bool checkWebcamAvailable();
    void webcamView();
// methods
    void newDir(QString dirPath);
    void delay();
    void viewStyle();

};

#endif // CAMERAWIDGET_H
