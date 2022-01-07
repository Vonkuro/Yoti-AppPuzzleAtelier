#include "cameraWidget.h"

CameraWidget::CameraWidget(QWidget *parent) :
    QWidget(parent)
{
// Init of attribut at application start
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

// Manage details of the view
void CameraWidget::viewStyle()
{
    photoButton->setText("Prendre une Photo");
    this->setMinimumHeight(1200);
    this->setMinimumWidth(1200);
    webcamViewfinder->setMaximumHeight(887);
    cameraLayout->setSizeConstraint(QLayout::SetMinimumSize);
}

// The end of the line for the pointers
CameraWidget::~CameraWidget()
{
    delete webcam;
    delete webcamViewfinder;
    delete webcamImageCapture;
    delete cameraLayout;
    delete photoButton;
}

// Check if there are Webcam (Future : choose the specific webcam)
bool CameraWidget::checkWebcamAvailable()
{
    if (QCameraInfo::availableCameras().count() > 0)
        return true;
    else
        return false;
}

// Prepare the webcam and the view of it's video feed
void CameraWidget::webcamView()
{
// Init of attributs for view of the webcam
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

// Prepare the directory to store the images
void CameraWidget::prepare(int id)
{
    puzzleId = id;
    pathImageDirectory = "Images/Puzzle-" + QString::number(puzzleId);
    newDir("../" + pathImageDirectory);
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

    delay(1000);

    emit photoTaken(puzzleId, lastImageId);
}

