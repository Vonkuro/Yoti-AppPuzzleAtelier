#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QtMultimediaWidgets>
#include <unistd.h>
#include "widgets_global.h"
#include "common.h"

class CameraWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraWidget(QWidget *parent = 0);
    ~CameraWidget();
// Tools for the Master Widget to Manage the Webcam
    void prepare(int id, QCameraInfo cameraInfo, bool forBoxPhoto);
    void start();
    void stop();

// Taking the photo
signals:
    void photoTaken(int idPuzzle, int idImage);
    void coverTaken(int idPuzzle);
private slots:
    void takePhoto();

private:
// Object managers of view
    QVBoxLayout* cameraLayout;
    QPushButton* photoButton;

    QLabel* logoLabel;
    QWidget* backgroundWidget;
    QVBoxLayout* backgroundLayout;

// Objects managers of webcam
    QCamera* webcam;
    QCameraViewfinder* webcamViewfinder;
    QCameraImageCapture* webcamImageCapture;
    QCameraViewfinderSettings viewfinderSettings;

// Attributs
    int puzzleId;
    int lastImageId;
    QString pathImageDirectory;
    bool cameraConfigured;
    bool boxPhoto;
// Methods to control and config the webcam
    bool checkWebcamAvailable();
    void webcamView(QCameraInfo cameraInfo);
// Methods
    void viewStyle();
    void cameraStyle();

};

#endif // CAMERAWIDGET_H
