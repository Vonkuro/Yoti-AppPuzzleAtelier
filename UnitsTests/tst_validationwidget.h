#ifndef TST_VALIDATIONWIDGET_H
#define TST_VALIDATIONWIDGET_H
#include <QtTest>
#include "validationWidget.h"

class tst_validationWidget: public QObject
{
    Q_OBJECT

public:
    tst_validationWidget();

    // Work in progress
private slots:
    void initTestCase();
    void cleanupTestCase();
    void validTest();
    void cancelTest();

private:
    ValidationWidget* validation;
    QString path;
};

#endif // TST_VALIDATIONWIDGET_H
