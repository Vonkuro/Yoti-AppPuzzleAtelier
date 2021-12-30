#ifndef MASTERWIDGET_H
#define MASTERWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "widgets_global.h"
#include "homepageWidget.h"
#include "cameraWidget.h"
#include "savePuzzleWidget.h"
#include "validationWidget.h"



class MasterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MasterWidget(QWidget *parent = 0);
    ~MasterWidget();
    bool testDuTest();
    void test();
    enum pages {homepage, savePuzzle, camera, validation, noPage};
    pages getLoadedPage();

private:
// objets manager of View and Widget
    QHBoxLayout* masterLayout;
    QStackedWidget* masterStackedWidget;
// Widgets
    HomepageWidget* homepageWidget;
    SavePuzzleWidget* savePuzzleWidget;
    CameraWidget* cameraWidget;
    ValidationWidget* validationWidget;
// methods


public slots:
    void goToWebcam(int id);
    void goToWebcam();
    void goToSavePuzzle();
    void goToValidation(int idPuzzle, int idImage);


};

#endif // MASTERWIDGET_H
