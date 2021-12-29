#include "cameraWidget.h"

CameraWidget::CameraWidget(int id, QWidget *parent) :
    QWidget(parent)
{
    puzzleId = id;
    if (checkWebcamAvailable())
    {
        webcamView();
    }
}

CameraWidget::~CameraWidget()
{
    delete webcam;
    delete webcamViewfinder;
    delete webcamImageCapture;
    delete cameraLayout;
}


bool CameraWidget::checkWebcamAvailable()
{
    if (QCameraInfo::availableCameras().count() > 0)
        return true;
    else
        return false;
}

void CameraWidget::test()
{

}

void CameraWidget::webcamView()
{
// init of attributs for view of the webcam
    webcam = new QCamera;
    webcamViewfinder = new QCameraViewfinder;
    viewfinderSettings.setResolution(1280, 960); //<- here for size of the viewFinder Widget created from webcamViewfinder

//Linking webcam to the widget
    webcam->setViewfinderSettings(viewfinderSettings);
    webcam->setViewfinder(webcamViewfinder);
    webcamImageCapture = new QCameraImageCapture(webcam, this);

//Starting the view
    cameraLayout = new QVBoxLayout;
    cameraLayout->addWidget(webcamViewfinder);

    this->setLayout(cameraLayout);
}

void CameraWidget::start()
{
    webcam->start();
}

void CameraWidget::stop()
{
    webcam->stop();
}
