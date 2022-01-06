#ifndef TST_HOMEPAGEWIDGET_H
#define TST_HOMEPAGEWIDGET_H

#include <QtTest>
#include "homepageWidget.h"


class tst_homepageWidget : public QObject
{
    Q_OBJECT

public:
    tst_homepageWidget();

private slots:
    void initTestCase();
    void startSignalTest();

private:
    HomepageWidget* homepage;
};

#endif // TST_HOMEPAGEWIDGET_H
