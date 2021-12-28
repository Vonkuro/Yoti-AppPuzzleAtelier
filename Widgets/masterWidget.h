#ifndef MASTERWIDGET_H
#define MASTERWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "widgets_global.h"


class MasterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MasterWidget(QWidget *parent = 0);
    ~MasterWidget();
    bool testDuTest();

private:
    QHBoxLayout* masterLayout;
    QStackedWidget* masterStackedWidget;
};

#endif // MASTERWIDGET_H
