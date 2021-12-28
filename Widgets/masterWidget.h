#ifndef MASTERWIDGET_H
#define MASTERWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "widgets_global.h"
#include "cameraWidget.h"
#include "savePuzzleWidget.h"


class MasterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MasterWidget(QWidget *parent = 0);
    ~MasterWidget();
    bool testDuTest();
    void test();

private:
// objets manager of View and Widget
    QHBoxLayout* masterLayout;
    QStackedWidget* masterStackedWidget;
// Widgets
    QWidget* blank;
    SavePuzzleWidget* savePuzzleWidget;
    CameraWidget* cameraWidget;
// methods


public slots:
    void gotToWebcam();
    void gotToSavePuzzle();

};

#endif // MASTERWIDGET_H
