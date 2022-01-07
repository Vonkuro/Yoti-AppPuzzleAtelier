#ifndef TST_MASTERWIDGET_H
#define TST_MASTERWIDGET_H
#include <QtTest>
#include "masterWidget.h"

class tst_masterWidget : public QObject
{
    Q_OBJECT
public:
    tst_masterWidget();
    ~tst_masterWidget();

// Declaration of the Tests
private slots:
    // Specials QT Tests at the launch at the start and the end of the Test Case
    void initTestCase(); // start
    //void cleanupTestCase(); // end

    // Unit-Tests of Methods
    void goToWebcamTest();
    void goToSavePuzzleTest();
    void goToScannerTest();



private:
    MasterWidget* master;
};

#endif // TST_MASTERWIDGET_H
