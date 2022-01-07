#ifndef TST_SCANNERWIDGET_H
#define TST_SCANNERWIDGET_H

#include <QtTest>
#include "scannerWidget.h"

class tst_scannerWidget : public QObject
{
    Q_OBJECT
public:
    tst_scannerWidget();

// Declaration of the Tests
private slots:
    // Specials QT Tests at the launch at the start and the end of the Test Case
    void initTestCase(); // start
    // Unit-Tests of Methods
    void prepareTest();

private:
    ScannerWidget* scanner;
};

#endif // TST_SCANNERWIDGET_H
