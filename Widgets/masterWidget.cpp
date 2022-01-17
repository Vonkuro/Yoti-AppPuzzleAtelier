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
    choiceCameraWidget = new ChoiceCameraWidget;
    cameraWidget = new CameraWidget();
    choiceScannerWidget = new ChoiceScannerWidget;
    scannerWidget = new ScannerWidget;
    validationWidget = new ValidationWidget;
    waittingWidget = new WaittingWidget;
    resultWidget = new ResultWidget;
// Linking the Widget to the stack
    masterStackedWidget->addWidget(homepageWidget);
    masterStackedWidget->addWidget(savePuzzleWidget);
    masterStackedWidget->addWidget(choiceCameraWidget);
    masterStackedWidget->addWidget(cameraWidget);
    masterStackedWidget->addWidget(choiceScannerWidget);
    masterStackedWidget->addWidget(scannerWidget);
    masterStackedWidget->addWidget(validationWidget);
    masterStackedWidget->addWidget(waittingWidget);
    masterStackedWidget->addWidget(resultWidget);

// Linking the Application together
    manager = new folderManager;
    datawrapper.setDatabase();
    connectTheApplication();

// View Style
    viewStyle();
// Init empty attribut
    deviceNameMemory = QString();
    cameraInfoMemory = QCameraInfo();
}

// The end of the line for the pointers
MasterWidget::~MasterWidget()
{
    delete homepageWidget;
    delete savePuzzleWidget;
    delete choiceCameraWidget;
    delete cameraWidget;
    delete choiceScannerWidget;
    delete scannerWidget;
    delete validationWidget;
    delete waittingWidget;
    delete resultWidget;
    delete manager;   
    delete masterStackedWidget;
    delete masterLayout;

    datawrapper.removeDatabase();
}


// This function is there in order to test if the unit-test setup is correct
bool MasterWidget::testDuTest()
{
    return true;
}

// Display the camera widget and give it the id of the puzzle
// Should always be the one used after saving the puzzle to the database
void MasterWidget::goToWebcam(int id, QCameraInfo cameraInfo)
{
    masterStackedWidget->setCurrentWidget(cameraWidget);

    cameraWidget->prepare(id, cameraInfo);

    cameraInfoMemory = cameraInfo;

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
void MasterWidget::goToScanner(int id, QString deviceName)
{
    scannerWidget->prepare(id, deviceName);

    deviceNameMemory = deviceName;

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

// Display the choice of camera widget
void MasterWidget::goToChoiceCamera(int id)
{
    choiceCameraWidget->searchCamera(id);
    masterStackedWidget->setCurrentWidget(choiceCameraWidget);
}

// Display the choice of scanner widget
void MasterWidget::goToChoiceScanner(int id)
{
    choiceScannerWidget->searchScanner(id);
    masterStackedWidget->setCurrentWidget(choiceScannerWidget);
}

// Display the waitting widget
void MasterWidget::goToWaitting(int id)
{
    masterStackedWidget->setCurrentWidget(waittingWidget);
    waittingWidget->solverProcessStart(id);
}

// Display the resultult widget
// Used when the puzzle is solved
void MasterWidget::goToResult(int numberPieces, bool completed)
{
    resultWidget->display(numberPieces, completed);
    masterStackedWidget->setCurrentWidget(resultWidget);
}

// Display the resultult widget
// Used when the puzzle is not solved
void MasterWidget::goToResult()
{
    resultWidget->display();
    masterStackedWidget->setCurrentWidget(resultWidget);
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
        if (cameraInfoMemory.isNull())
        {
            goToChoiceCamera(id);
        } else
        {
            goToWebcam(id, cameraInfoMemory);
        }

    }
    // choice is scanner
    else
    {
        chosenDevice = Scanner;
        if (deviceNameMemory.isNull())
        {
            goToChoiceScanner(id);
        } else
        {
            goToScanner(id, deviceNameMemory);
        }

    }
}

// Launch the archive process
void MasterWidget::archive()
{
    manager->tarOldImageFolder();
}

// Connects the widget "end" signal the changing display slots
// Connects the backgrounds process to their signals
void MasterWidget::connectTheApplication()
{
    // these testing connect will be almost good to go for the full application
    connect(homepageWidget, &HomepageWidget::startApp, this, &MasterWidget::goToSavePuzzle); 
    connect(savePuzzleWidget, SIGNAL(puzzleSaved(int)) , this, SLOT(choiceImageAcquisition(int)));

    connect(choiceCameraWidget, SIGNAL(cameraSetUp(int, QCameraInfo)) , this, SLOT(goToWebcam(int,QCameraInfo)));
    connect(cameraWidget, SIGNAL(photoTaken(int,int)), this, SLOT(goToValidation(int, int)));

    connect(choiceScannerWidget, SIGNAL(scannerSetUp(int, QString)) , this, SLOT(goToScanner(int,QString)));
    connect(scannerWidget, SIGNAL(photoTaken(int,int)), this, SLOT(goToValidation(int, int)));

    connect(validationWidget, SIGNAL(newPhoto()), this, SLOT(goToPhotoDevice()));
    connect(validationWidget, SIGNAL(allIsValidated(int)), this, SLOT(goToWaitting(int)));

    connect(waittingWidget, SIGNAL(puzzleSolved(int,bool)), this, SLOT(goToResult(int,bool)));
    connect(waittingWidget, SIGNAL(puzzleNotSolved()), this, SLOT(goToResult()));

    connect(resultWidget, &ResultWidget::restart, this, &MasterWidget::goToSavePuzzle);
}


void MasterWidget::viewStyle()
{
// Application size
    QSize applicationSize(1260,980);
    masterStackedWidget->setMaximumSize(applicationSize);
// Adding the font of Yoti to the Application
    QFontDatabase::addApplicationFont(":/viewRessource/Montserrat-SemiBold");
    QFontDatabase::addApplicationFont(":/viewRessource/Montserrat");
    QFontDatabase::addApplicationFont(":/viewRessource/Poppins-Medium");
    QFontDatabase::addApplicationFont(":/viewRessource/Poppins-Bold");

// Common StyleSheet
    QString StyleSheet = "QLabel[cssClass=\"title\"] { font: bold \"Montserrat\"; font-size: 42px; color: #2C2E71}";
    StyleSheet += "QLabel[cssClass=\"subtitle\"] { font: \"Montserrat\"; font-size: 22px; color: #6569C4}" ;
    StyleSheet += "QPushButton[cssClass=\"greenButton\"] {font: bold \"Montserrat\"; font-size: 28px; color: #2C2E71; "
                                                        "background-color: #78C29B; border: 2px solid #6569C4; "
                                                        "height: 50px; max-width: 500px; padding-right: 150px; padding-left: 150px}";
    StyleSheet +="QLabel[cssClass=\"logoTitle\"] {max-width: 960px} ";

    this->setStyleSheet(StyleSheet);
}
