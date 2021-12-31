#include "cameraWidget.h"

CameraWidget::CameraWidget(QWidget *parent) :
    QWidget(parent)
{
// init of attribut at application start
    lastImageId = 0;
// Prepare the view
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

// manage details of the view
void CameraWidget::viewStyle()
{
    photoButton->setText("Prendre une Photo");
    this->setMinimumHeight(1200);
    this->setMinimumWidth(1200);
    webcamViewfinder->setMaximumHeight(887);
    cameraLayout->setSizeConstraint(QLayout::SetMinimumSize);
}

// the end of the line for the pointers
CameraWidget::~CameraWidget()
{
    delete webcam;
    delete webcamViewfinder;
    delete webcamImageCapture;
    delete cameraLayout;
    delete photoButton;
}

// check if there are Webcam (Future : choose the specific webcam)
bool CameraWidget::checkWebcamAvailable()
{
    if (QCameraInfo::availableCameras().count() > 0)
        return true;
    else
        return false;
}

// prepare the webcam and the view of it's video feed
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

// Give the Master Widget the ability to start and stop the webcam
void CameraWidget::start()
{
    webcam->start();
}

void CameraWidget::stop()
{
    webcam->stop();
}

// prepare the directory to store the images
void CameraWidget::prepare(int id)
{
    puzzleId = id;
    pathImageDirectory = "Images/Puzzle-" + QString::number(puzzleId);
    newDir("../" + pathImageDirectory);
}

// create a directory if it doesn't exit
void CameraWidget::newDir(QString dirPath)
{
    QDir dir(dirPath);
    QDir dir2;
    if(!dir.exists())
    {
        dir2.mkpath(dirPath);
    }
}

// Take the photo
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

// delay the widget loop for 1 second
void CameraWidget::delay()
{
    QTime dieTime = QTime::currentTime().addMSecs(1000);

    while(QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
