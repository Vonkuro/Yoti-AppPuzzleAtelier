#include "masterWidget.h"
#include "ui_masterWidget.h"

MasterWidget::MasterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MasterWidget)
{
    ui->setupUi(this);
}

MasterWidget::~MasterWidget()
{
    delete ui;
}

bool MasterWidget::testDuTest()
{
    return true;
}
