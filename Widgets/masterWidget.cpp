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

// Display the save puzzle widget
void MasterWidget::goToSavePuzzle()
{
    masterStackedWidget->setCurrentWidget(savePuzzleWidget);
}

// Display the validation widget
void MasterWidget::goToValidation(int idPuzzle, int idImage)
{
    validationWidget->validateImageWebcam(idPuzzle, idImage);
    masterStackedWidget->setCurrentWidget(validationWidget);
}

void MasterWidget::goToScanner(int id)
{
    scannerWidget->prepare(id);
    masterStackedWidget->setCurrentWidget(scannerWidget);
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
    else
    {
        return noPage;
    }

}

// Connects the widget "end" signal the changing display slots
// It is used for testing until I made all the widget and I write an equivalent
// for the constructor
void MasterWidget::test()
{
    // these testing connect will be almost good to go for the full application
    connect(homepageWidget, &HomepageWidget::startApp, this, &MasterWidget::goToSavePuzzle);
    connect(savePuzzleWidget, SIGNAL(puzzleSaved(int)) , this, SLOT(goToScanner(int)));
    connect(cameraWidget, SIGNAL(photoTaken(int,int)), this, SLOT(goToValidation(int, int)));
    connect(validationWidget, SIGNAL(newPhoto()), this, SLOT(goToWebcam()));
}
