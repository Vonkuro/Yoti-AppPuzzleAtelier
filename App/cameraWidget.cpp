#include "cameraWidget.h"
#include "ui_cameraWidget.h"

CameraWidget::CameraWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraWidget)
{
    ui->setupUi(this);

}

CameraWidget::~CameraWidget()
{
    delete ui;
    //delete webcam;
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
    if (checkWebcamAvailable())
    {
        webcamView();

    }

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
    webcam->start();
    ui->webcamLayout->addWidget(webcamViewfinder);
    this->setLayout(ui->webcamLayout);


}
