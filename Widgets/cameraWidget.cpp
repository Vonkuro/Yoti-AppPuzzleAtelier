#include "cameraWidget.h"

CameraWidget::CameraWidget(QWidget *parent) :
    QWidget(parent)
{
    lastImageId = 0;

    if (checkWebcamAvailable())
    {
        photoButton = new QPushButton;
        webcamView();
        cameraLayout->addWidget(photoButton);
        this->setLayout(cameraLayout);
        connect(photoButton, &QPushButton::clicked, this, &CameraWidget::takePhoto);
        viewStyle();
    }
}

void CameraWidget::viewStyle()
{
    photoButton->setText("Prendre une Photo");
    this->setMinimumHeight(1200);
    this->setMinimumWidth(1200);
    webcamViewfinder->setMaximumHeight(887);
    cameraLayout->setSizeConstraint(QLayout::SetMinimumSize);
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
    webcam->setCaptureMode(QCamera::CaptureStillImage);


//Starting the view
    cameraLayout = new QVBoxLayout;
    cameraLayout->addWidget(webcamViewfinder);
}

void CameraWidget::start()
{
    webcam->start();
}

void CameraWidget::prepare(int id)
{
    puzzleId = id;
    pathImageDirectory = "Images/Puzzle-" + QString::number(puzzleId);
    newDir("../" + pathImageDirectory);
}

void CameraWidget::stop()
{
    webcam->stop();
}

void CameraWidget::newDir(QString dirPath)
{
    QDir dir(dirPath);
    QDir dir2;
    if(!dir.exists())
    {
        dir2.mkpath(dirPath);
    }
}

void CameraWidget::takePhoto()
{
    ++lastImageId;
    webcam->searchAndLock();
    //
    QString imagePath = qApp->applicationDirPath() + "/../" + pathImageDirectory + "/image-" + QString::number(lastImageId) + ".jpg";
    webcamImageCapture->capture(imagePath);
    webcam->unlock();

    stop();

    delay();

    emit photoTaken(puzzleId, lastImageId);
}

void CameraWidget::delay()
{
    QTime dieTime = QTime::currentTime().addMSecs(500);

    while(QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
