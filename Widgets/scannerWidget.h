#ifndef SCANNERWIDGET_H
#define SCANNERWIDGET_H

#include <QWidget>
#include <QDebug>
#include "widgets_global.h"
#include "sane/sane.h"
#include "sane/saneopts.h"
#include "hello_sane.h"

class ScannerWidget: public QWidget
{
    Q_OBJECT
public:
    ScannerWidget();
    void prepareScanner();
private:
// view object manager

// Attributs managing the scanner
    SANE_Int version;
    SANE_Status goodToGo;
    const SANE_Device ** deviceList;
    const SANE_Device* device;
    SANE_Handle* scannerHandler;
// Methods managing the scanner


};

#endif // SCANNERWIDGET_H
