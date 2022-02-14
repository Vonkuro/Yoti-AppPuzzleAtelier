#include "cameraWidget.h"

CameraWidget::CameraWidget(QWidget *parent) :
    QWidget(parent)
{
// Init of attribut at application start
    lastImageId = 0;
    cameraLayout = NULL;
    photoButton = NULL;
    webcam = NULL;
    webcamViewfinder = NULL;
    webcamImageCapture = NULL;
    cameraConfigured = false;

// Prepare the view
    if (checkWebcamAvailable())
    {
        // Init of view objects
        cameraLayout = new QVBoxLayout;
        logoLabel = new QLabel;
        backgroundWidget = new QWidget;
        backgroundLayout = new QVBoxLayout(backgroundWidget);
        photoButton = new QPushButton;

        // Linking the view objects
        cameraLayout->addWidget(logoLabel);
        cameraLayout->addWidget(backgroundWidget);
        cameraLayout->addWidget(photoButton);

        this->setLayout(cameraLayout);

        // Connect the slots and signals
        connect(photoButton, &QPushButton::clicked, this, &CameraWidget::takePhoto);

        // Style my widget !
        viewStyle();
    }
}

// Manage details of the view
void CameraWidget::viewStyle()
{
    QPixmap logo(":/viewRessource/logoYoti");
    logoLabel->setProperty("cssClass","logo");
    logoLabel->setScaledContents(true);
    logoLabel->setPixmap(logo);
    cameraLayout->setAlignment(logoLabel,Qt::AlignHCenter);

    backgroundWidget->setObjectName("background");
    backgroundWidget->setStyleSheet("#background {background-color: #2C2E71; max-width: 914px; min-width: 914px; max-height: 690px; min-height: 690px;}");
    cameraLayout->setAlignment(backgroundWidget,Qt::AlignHCenter);

    photoButton->setText("Prendre la Photographie");
    photoButton->setProperty("cssClass","greenButton");
    cameraLayout->setAlignment(photoButton,Qt::AlignHCenter);


}

// Manage details of the view of the webcamViewfinder
void CameraWidget::cameraStyle()
{
    cameraLayout->setSizeConstraint(QLayout::SetMinimumSize);
    webcamViewfinder->setMaximumHeight(887);
}

// The end of the line for the pointers
CameraWidget::~CameraWidget()
{
    if (webcam)
    {
       delete webcam;
    }
    if (webcamViewfinder)
    {
        delete webcamViewfinder;
    }
    delete logoLabel;
    delete webcamImageCapture;
    delete photoButton;
    delete cameraLayout;
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
void CameraWidget::webcamView(QCameraInfo cameraInfo)
{
// Init of attributs for view of the webcam
    webcam = new QCamera(cameraInfo);
    webcamViewfinder = new QCameraViewfinder;
    viewfinderSettings.setResolution(1280, 960); //<- here for size of the viewFinder Widget created from webcamViewfinder

//Linking webcam to the widget
    webcam->setViewfinderSettings(viewfinderSettings);
    webcam->setViewfinder(webcamViewfinder);
    webcamImageCapture = new QCameraImageCapture(webcam, this);
    webcam->setCaptureMode(QCamera::CaptureStillImage);


//Starting the view

    backgroundLayout->addWidget(webcamViewfinder);

    cameraConfigured =true;

}

// Give the Master Widget the ability to start and stop the webcam
void CameraWidget::start()
{
    photoButton->setStyleSheet(greenButtonBackgroundStyle);
    webcam->start();

    photoButton->setEnabled(true);
}
void CameraWidget::stop()
{
    webcam->stop();
}

// Prepare the directory to store the images
void CameraWidget::prepare(int id, QCameraInfo cameraInfo, bool forBoxPhoto)
{
    puzzleId = id;
    boxPhoto = forBoxPhoto;

    QString home = QDir::homePath();
    pathImageDirectory = home + "/Yoti-AppPuzzle/Images/Puzzle-" + QString::number(puzzleId);
    newDir(pathImageDirectory);
    if (forBoxPhoto)
    {
        newDir(pathImageDirectory + "/Cover");
    }
    if (! cameraConfigured)
    {
        webcamView(cameraInfo);

        cameraStyle();
    }
}


// Take the photo
void CameraWidget::takePhoto()
{
    photoButton->setEnabled(false);

    photoButton->setStyleSheet(greenCheckedButtonBackgroundStyle);

    if (boxPhoto)
    {
        webcam->searchAndLock();
        QString imagePath = pathImageDirectory + "/Cover/box.jpg";
        webcamImageCapture->capture(imagePath);
        webcam->unlock();

        stop();

        delay(1000);

        emit coverTaken(puzzleId);
    }else{
        ++lastImageId;
        webcam->searchAndLock();

        QString imagePath = pathImageDirectory + "/image-" + QString::number(lastImageId) + ".jpg";
        webcamImageCapture->capture(imagePath);
        webcam->unlock();

        stop();

        delay(1000);

        emit photoTaken(puzzleId, lastImageId);
    }

}

void CameraWidget::idToContinue()
{
    lastImageId += 100;
}
