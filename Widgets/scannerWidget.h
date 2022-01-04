#ifndef SCANNERWIDGET_H
#define SCANNERWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QDebug>
#include "widgets_global.h"
#include "hello_sane.h"

class ScannerWidget: public QWidget
{
    Q_OBJECT
public:
    ScannerWidget();
    ~ScannerWidget();
// Tools for the master widget
    void prepare(int id);
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
// Methods
    void newDir(QString dirPath);
};

#endif // SCANNERWIDGET_H
