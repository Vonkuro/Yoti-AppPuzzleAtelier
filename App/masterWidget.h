#ifndef MASTERWIDGET_H
#define MASTERWIDGET_H

#include <QWidget>

namespace Ui {
class MasterWidget;
}

class MasterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MasterWidget(QWidget *parent = 0);
    ~MasterWidget();
    bool testDuTest();

private:
    Ui::MasterWidget *ui;
};

#endif // MASTERWIDGET_H
