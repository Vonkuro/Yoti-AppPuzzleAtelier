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


//this function is there in order to test if the unit-test setup is correct
bool MasterWidget::testDuTest()
{
    return true;
}
