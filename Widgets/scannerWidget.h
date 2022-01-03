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
    void init_v2();
private:
// view object manager

// Attributs managing the scanner
    SANE_Int version;
    const SANE_Device ** device_list;
    const SANE_Device* device;
    SANE_Handle* scannerHandler;
// Methods managing the scanner

    static void auth_callback (SANE_String_Const resource,
                               SANE_Char * username, SANE_Char * password)
    {}
};

#endif // SCANNERWIDGET_H
