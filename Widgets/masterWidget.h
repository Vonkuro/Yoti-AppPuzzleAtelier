#ifndef MASTERWIDGET_H
#define MASTERWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "envLocal.h"
#include "widgets_global.h"
#include "homepageWidget.h"
#include "choiceCameraWidget.h"
#include "cameraWidget.h"
#include "savePuzzleWidget.h"
#include "validationWidget.h"
#include "choiceScannerWidget.h"
#include "scannerWidget.h"
#include "folderManager.h"

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
// Attributs
    enum photoDevice {Webcam, Scanner};
    photoDevice chosenDevice;
// Methods
    void connectTheApplication();
// Objects tools
    folderManager* manager;


public slots:
// Slots managers of which widget is on screen
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
// Slots mangers of background process
    void archive();


};

#endif // MASTERWIDGET_H
