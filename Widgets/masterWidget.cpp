#include "masterWidget.h"

MasterWidget::MasterWidget(QWidget *parent) :
    QWidget(parent)
{

    datawrapper.setDatabase();

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
    resultAtelierWidget = new ResultAtelierWidget;
// Linking the Widget to the stack
    masterStackedWidget->addWidget(homepageWidget);
    masterStackedWidget->addWidget(savePuzzleWidget);
    masterStackedWidget->addWidget(choiceCameraWidget);
    masterStackedWidget->addWidget(cameraWidget);
    masterStackedWidget->addWidget(choiceScannerWidget);
    masterStackedWidget->addWidget(scannerWidget);
    masterStackedWidget->addWidget(validationWidget);
    masterStackedWidget->addWidget(resultAtelierWidget);
// Linking the Application together
    connectTheApplication();

// View Style
    viewStyle();
// Init empty attribut
    deviceNameMemory = QString();
    cameraInfoMemory = QCameraInfo();

    nightDeamon();
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

    cameraWidget->prepare(id, cameraInfo, boxCoverNotTaken);

    cameraInfoMemory = cameraInfo;

    cameraWidget->start();

    if (boxCoverNotTaken)
    {
        boxCoverNotTaken = false;
    }
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
    scannerWidget->prepare();
    masterStackedWidget->setCurrentWidget(scannerWidget);
}

// Display the save puzzle widget
void MasterWidget::goToSavePuzzle()
{
    boxCoverNotTaken = true;
    savePuzzleWidget->prepare();
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
    validationWidget->validateImageWebcam(idPuzzle, idImage, chosenDevice);
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

void MasterWidget::goToResultAtelier()
{
    if (resultAtelierWidget->isThereResult())
    {
        masterStackedWidget->setCurrentWidget(resultAtelierWidget);
    } else
    {
        goToSavePuzzle();
    }
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

    QList<QAbstractButton *> buttons = choiceImage.buttons();
    for (QAbstractButton * button : buttons)
    {
        button->setProperty("cssClass","greenButton");
    }
    choiceImage.setStyleSheet( "QLabel {font: \"Montserrat\"; color: #2C2E71}"
                              "QMessageBox {background-color: white}"
                              "QPushButton[cssClass=\"greenButton\"]  {font: bold \"Montserrat\"; font-size: 22px; color: #2C2E71; "
                              "background-color: #78C29B; border: 2px solid #6569C4;}");


    int choice = choiceImage.exec();
    // choice is webcam
    if(choice == 0)
    {
        chosenDevice = Webcam;

        goToChoiceCamera(id);


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

// Find if the bakcground process is not running
// Return true if it isn't
bool MasterWidget::nightDeamonNotOn()
{
    QString commandString = "pgrep Yoti-AppPuzzled";
    std::string command = commandString.toStdString();
    QString result = QString::fromStdString( execute(command) );

    return (result.size() == 0);
}

// Run the background process if needed
void MasterWidget::nightDeamon()
{
    if ( nightDeamonNotOn() )
    {
        QString commandString = "../AppWork/Yoti-AppPuzzled &";
        std::string command = commandString.toStdString();
        system(command.c_str());
    }
}

// Update the database, the Puzzle is handled = false instead of handled = null
// Go to the Save Puzzle Widget
void MasterWidget::end(int id)
{
    QSqlDatabase database = datawrapper.getDatabase();

    if ( database.open())
    {
        QSqlQuery needToHandle(database);
        needToHandle.prepare("UPDATE Puzzle SET handled = FALSE WHERE id = ?;");
        needToHandle.bindValue(0,id);
        needToHandle.exec();

        database.close();
    }

    goToSavePuzzle();
}

// Connects the widget "end" signal the changing display slots
// Connects the backgrounds process to their signals
void MasterWidget::connectTheApplication()
{
    // these testing connect will be almost good to go for the full application
    connect(homepageWidget, &HomepageWidget::startApp, this, &MasterWidget::goToResultAtelier);

    connect(resultAtelierWidget, &ResultAtelierWidget::resultHandled, this, &MasterWidget::goToSavePuzzle);

    connect(savePuzzleWidget, SIGNAL(puzzleSaved(int)) , this, SLOT(goToChoiceCamera(int)));

    connect(cameraWidget, SIGNAL(coverTaken(int)), this, SLOT(choiceImageAcquisition(int)));

    connect(choiceCameraWidget, SIGNAL(cameraSetUp(int, QCameraInfo)) , this, SLOT(goToWebcam(int,QCameraInfo)));
    connect(cameraWidget, SIGNAL(photoTaken(int,int)), this, SLOT(goToValidation(int, int)));

    connect(choiceScannerWidget, SIGNAL(scannerSetUp(int, QString)) , this, SLOT(goToScanner(int,QString)));
    connect(scannerWidget, SIGNAL(photoTaken(int,int)), this, SLOT(goToValidation(int, int)));

    connect(validationWidget, SIGNAL(newPhoto()), this, SLOT(goToPhotoDevice()));
    connect(validationWidget, SIGNAL(allIsValidated(int)), this, SLOT(end(int)));

}

// Manage details of the view
void MasterWidget::viewStyle()
{
// Application size
    QSize applicationSize(1260,980);
    masterStackedWidget->setMaximumSize(applicationSize);
    masterStackedWidget->setMinimumSize(applicationSize);
// Adding the font of Yoti to the Application
    QFontDatabase::addApplicationFont(":/viewRessource/Montserrat-SemiBold");
    QFontDatabase::addApplicationFont(":/viewRessource/Montserrat");
    QFontDatabase::addApplicationFont(":/viewRessource/Poppins-Medium");
    QFontDatabase::addApplicationFont(":/viewRessource/Poppins-Bold");
// Pages
    this->setObjectName("window");
// Common StyleSheet
    QString StyleSheet = "#window {background-color: white} ";
    StyleSheet += "QLabel[cssClass=\"title\"] { font: bold \"Montserrat\"; font-size: 42px; color: #2C2E71} ";
    StyleSheet += "QLabel[cssClass=\"subtitle\"] { font: \"Montserrat\"; font-size: 22px; color: #6569C4}" ;
    StyleSheet += "QPushButton[cssClass=\"greenButton\"] {"+ greenButtonFontStyle +
                                                        " " + greenButtonBackgroundStyle +
                                                        " " + greenButtonSizeStyle +" } ";
    StyleSheet += "QLabel[cssClass=\"logoTitle\"] {max-width: 625px; max-height: 220px} ";
    StyleSheet += "QLabel[cssClass=\"logo\"] {max-width: 312; max-height: 110px } ";
    StyleSheet += "QComboBox[cssClass=\"choice\"] {height: 50px; max-width: 800px; min-width: 800px; }";

    this->setStyleSheet(StyleSheet);
}
