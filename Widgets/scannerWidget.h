#ifndef SCANNERWIDGET_H
#define SCANNERWIDGET_H

#include <QDebug>
#include <stdlib.h>
#include <string.h>
#include "widgets_global.h"
#include "common.h"

class ScannerWidget: public QWidget
{
    Q_OBJECT
public:
    ScannerWidget();
    ~ScannerWidget();
// Tools for the master widget
    void prepare(int id, QString deviceName);
    void prepare();

// Taking the photo
signals:
    void photoTaken(int idPuzzle, int idImage);

private:
// view object manager
    QVBoxLayout* widgetLayout;
    QPushButton* scanButton;
    QLabel* logoLabel;
    QLabel* titleLabel;
    QLabel* subTitleOneLabel;
    QLabel* subTitleTwoLabel;
    QLabel* subTitleThreeLabel;

// Methods managing the scanner
    void scanPuzzle();

// Attributs
    int puzzleId;
    int lastImageId;
    QString pathImageDirectory;
    QString scannerName;
// Methods
    void viewStyle();
};

#endif // SCANNERWIDGET_H
