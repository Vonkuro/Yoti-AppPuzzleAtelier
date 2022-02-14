#ifndef MASTERWIDGET_H
#define MASTERWIDGET_H

#include "common.h"
#include "envLocal.h"
#include "widgets_global.h"
#include "homepageWidget.h"
#include "choiceCameraWidget.h"
#include "cameraWidget.h"
#include "savePuzzleWidget.h"
#include "validationWidget.h"
#include "choiceScannerWidget.h"
#include "scannerWidget.h"
#include "resultAtelierWidget.h"

class MasterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MasterWidget(QWidget *parent = 0);
    ~MasterWidget();
// Methods for testing purposes
    bool testDuTest();
    enum pages {homepage, savePuzzle, camera, validation, scanner, noPage};
    pages getLoadedPage();

private:
// Objets manager of View and Widget
    QHBoxLayout* masterLayout;
    QStackedWidget* masterStackedWidget;
// Widgets
    HomepageWidget* homepageWidget;
    SavePuzzleWidget* savePuzzleWidget;
    ChoiceCameraWidget* choiceCameraWidget;
    CameraWidget* cameraWidget;
    ChoiceScannerWidget* choiceScannerWidget;
    ScannerWidget* scannerWidget;
    ValidationWidget* validationWidget;
    ResultAtelierWidget* resultAtelierWidget;
// Attributs
    photoDevice chosenDevice;
    QCameraInfo cameraInfoMemory;
    QString deviceNameMemory;
    bool boxCoverNotTaken;
// Methods
    void connectTheApplication();
    void viewStyle();
// Database
    EnvLocal datawrapper;

public slots:
// Slots managers of which widget is on screen
    void continueImageAcquisition(int id);
    void choiceImageAcquisition(int id);
    void goToWebcam(int id, QCameraInfo cameraInfo);
    void goToWebcam();
    void goToScanner(int id, QString deviceName);
    void goToScanner();
    void goToSavePuzzle();
    void goToPhotoDevice();
    void goToValidation(int idPuzzle, int idImage);
    void goToChoiceCamera(int id);
    void goToChoiceScanner(int id);
    void goToResultAtelier();
    void end(int id);
// Slots mangers of background process
    bool nightDeamonNotOn();
    void nightDeamon();


};

#endif // MASTERWIDGET_H
