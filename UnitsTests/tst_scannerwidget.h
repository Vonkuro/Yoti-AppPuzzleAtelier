#ifndef TST_SCANNERWIDGET_H
#define TST_SCANNERWIDGET_H

#include <QtTest>
#include "scannerWidget.h"

class tst_scannerWidget : public QObject
{
    Q_OBJECT
public:
    tst_scannerWidget();

private slots:
    void initTestCase();
    void prepareTest();

private:
    ScannerWidget* scanner;
};

#endif // TST_SCANNERWIDGET_H
