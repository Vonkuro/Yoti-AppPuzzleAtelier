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

private slots:
    void initTestCase();
    //void cleanupTestCase();

    void goToWebcamTest();
    void goToSavePuzzleTest();
    void goToScannerTest();
/*
    void goToPhotoDeviceTest();
    void goToWebcamIntTest();
    void goToScannerIntTest();
    void goToValidationTest();
*/


private:
    MasterWidget* master;
};

#endif // TST_MASTERWIDGET_H
