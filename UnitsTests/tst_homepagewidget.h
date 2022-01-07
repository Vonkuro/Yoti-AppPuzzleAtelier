#ifndef TST_HOMEPAGEWIDGET_H
#define TST_HOMEPAGEWIDGET_H

#include <QtTest>
#include "homepageWidget.h"


class tst_homepageWidget : public QObject
{
    Q_OBJECT

public:
    tst_homepageWidget();

// Declaration of the Tests
private slots:
    // Specials QT Tests at the launch at the start and the end of the Test Case
    void initTestCase(); // start
    // Unit-Tests of Methods
    void startSignalTest();

private:
    HomepageWidget* homepage;
};

#endif // TST_HOMEPAGEWIDGET_H
