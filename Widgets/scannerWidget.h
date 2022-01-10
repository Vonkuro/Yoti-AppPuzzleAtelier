#ifndef SCANNERWIDGET_H
#define SCANNERWIDGET_H

#include <QWidget>
#include <QtWidgets>
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

// Taking the photo
signals:
    void photoTaken(int idPuzzle, int idImage);

private:
// view object manager
    QVBoxLayout* widgetLayout;
    QPushButton* scanButton;

// Methods managing the scanner
    void scanPuzzle();

// Attributs
    int puzzleId;
    int lastImageId;
    QString pathImageDirectory;
    QString scannerName;
// Methods
};

#endif // SCANNERWIDGET_H
