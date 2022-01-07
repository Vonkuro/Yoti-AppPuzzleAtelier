#ifndef TST_VALIDATIONWIDGET_H
#define TST_VALIDATIONWIDGET_H
#include <QtTest>
#include "validationWidget.h"

class tst_validationWidget: public QObject
{
    Q_OBJECT

public:
    tst_validationWidget();

// Declaration of the Tests
private slots:
    // Specials QT Tests at the launch at the start and the end of the Test Case
    void initTestCase(); // start
    void cleanupTestCase(); //end
    // Unit-Tests of Methods
    void cancelTest();

private:
    ValidationWidget* validation;
    QString path;
};

#endif // TST_VALIDATIONWIDGET_H
