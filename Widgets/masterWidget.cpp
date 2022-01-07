#include "masterWidget.h"

MasterWidget::MasterWidget(QWidget *parent) :
    QWidget(parent)
{
// Setup minimal view
    masterLayout = new QHBoxLayout;
    masterStackedWidget = new QStackedWidget;

    masterLayout->addWidget(masterStackedWidget);
    setLayout(masterLayout);

// Loading Widgets
    homepageWidget = new HomepageWidget;
    savePuzzleWidget = new SavePuzzleWidget;
    cameraWidget = new CameraWidget();
    scannerWidget = new ScannerWidget;
    validationWidget = new ValidationWidget;

    masterStackedWidget->addWidget(homepageWidget);
    masterStackedWidget->addWidget(savePuzzleWidget);
    masterStackedWidget->addWidget(cameraWidget);
    masterStackedWidget->addWidget(scannerWidget);
    masterStackedWidget->addWidget(validationWidget);

}

// The end of the line for the pointers
MasterWidget::~MasterWidget()
{
    delete masterLayout;
    delete masterStackedWidget;
    delete homepageWidget;
    delete savePuzzleWidget;
    delete cameraWidget;
    delete scannerWidget;
    delete validationWidget;
}


// This function is there in order to test if the unit-test setup is correct
bool MasterWidget::testDuTest()
{
    return true;
}

// Display the camera widget and give it the id of the puzzle
// Should always be the one used after saving the puzzle to the database
void MasterWidget::goToWebcam(int id)
{
    masterStackedWidget->setCurrentWidget(cameraWidget);

    cameraWidget->prepare(id);
    cameraWidget->start();
}

// Display the camera widget
// Should be the one used after the validation of a photo
void MasterWidget::goToWebcam()
{
    masterStackedWidget->setCurrentWidget(cameraWidget);

    cameraWidget->start();
}

// Display the scanner widget and give it the id of the puzzle
// Should always be the one used after saving the puzzle to the database
void MasterWidget::goToScanner(int id)
{
    scannerWidget->prepare(id);
    masterStackedWidget->setCurrentWidget(scannerWidget);
}

// Display the scanner widge
// Should be the one used after the validation of a photo
void MasterWidget::goToScanner()
{
    masterStackedWidget->setCurrentWidget(scannerWidget);
}

// Display the save puzzle widget
void MasterWidget::goToSavePuzzle()
{
    masterStackedWidget->setCurrentWidget(savePuzzleWidget);
}

// Redirect to the correct photographic device in function of chosenDevice
void MasterWidget::goToPhotoDevice()
{
    if (chosenDevice == Webcam)
    {
        goToWebcam();
    }
    else if (chosenDevice == Scanner)
    {
        goToScanner();
    }
}

// Display the validation widget
void MasterWidget::goToValidation(int idPuzzle, int idImage)
{
    validationWidget->validateImageWebcam(idPuzzle, idImage);
    masterStackedWidget->setCurrentWidget(validationWidget);
}

// Return a page keyword that describe the widget displayed on screen
MasterWidget::pages MasterWidget::getLoadedPage()
{
    QWidget* currentWidget = masterStackedWidget->currentWidget();

    if (currentWidget == homepageWidget)
    {
        return homepage;
    }
    else if (currentWidget == savePuzzleWidget)
    {
        return savePuzzle;
    }
    else if (currentWidget == cameraWidget)
    {
        return camera;
    }
    else if (currentWidget == validationWidget)
    {
        return validation;
    }
    else if (currentWidget == scannerWidget)
    {
        return scanner;
    }
    else
    {
        return noPage;
    }

}

// Open a message box in order to let the user chose which device with be used for the photos
void MasterWidget::choiceImageAcquisition(int id)
{
    QMessageBox choiceImage;
    choiceImage.addButton("Webcam", QMessageBox::YesRole);
    choiceImage.addButton("Imprimante", QMessageBox::NoRole);
    choiceImage.setText("Quel périphérique allez-vous utiliser pour prendre des photographies du Puzzle ?");
    int choice = choiceImage.exec();
    // choice is webcam
    if(choice == 0)
    {
        chosenDevice = Webcam;
        goToWebcam(id);
    }
    // choice is scanner
    else
    {
        chosenDevice = Scanner;
        goToScanner(id);
    }
}

// Launch the archive process
void MasterWidget::archive()
{
    manager.tarOldImageFolder();
}

// Connects the widget "end" signal the changing display slots
// It is used for testing until I made all the widget and I write an equivalent
// for the constructor
void MasterWidget::test()
{
    // these testing connect will be almost good to go for the full application
    connect(homepageWidget, &HomepageWidget::startApp, this, &MasterWidget::goToSavePuzzle);
    connect(savePuzzleWidget, SIGNAL(puzzleSaved(int)) , this, SLOT(choiceImageAcquisition(int)));
    connect(cameraWidget, SIGNAL(photoTaken(int,int)), this, SLOT(goToValidation(int, int)));
    connect(scannerWidget, SIGNAL(photoTaken(int,int)), this, SLOT(goToValidation(int, int)));
    connect(validationWidget, SIGNAL(newPhoto()), this, SLOT(goToPhotoDevice()));
    connect(validationWidget, SIGNAL(allIsValidated(int)), this, SLOT(archive()));
}
