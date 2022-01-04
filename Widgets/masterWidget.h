#ifndef MASTERWIDGET_H
#define MASTERWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "widgets_global.h"
#include "homepageWidget.h"
#include "cameraWidget.h"
#include "savePuzzleWidget.h"
#include "validationWidget.h"
#include "scannerWidget.h"


class MasterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MasterWidget(QWidget *parent = 0);
    ~MasterWidget();
// Methods for testing purposes
    bool testDuTest();
    void test();
    enum pages {homepage, savePuzzle, camera, validation, noPage};
    pages getLoadedPage();

private:
// Objets manager of View and Widget
    QHBoxLayout* masterLayout;
    QStackedWidget* masterStackedWidget;
// Widgets
    HomepageWidget* homepageWidget;
    SavePuzzleWidget* savePuzzleWidget;
    CameraWidget* cameraWidget;
    ValidationWidget* validationWidget;
    ScannerWidget* scannerWidget;
// Methods


public slots:
// Slots managers of which widget is on screen
    void choiceImageAcquisition(int id);
    void goToWebcam(int id);
    void goToWebcam();
    void goToScanner(int id);
    void goToSavePuzzle();
    void goToValidation(int idPuzzle, int idImage);



};

#endif // MASTERWIDGET_H
