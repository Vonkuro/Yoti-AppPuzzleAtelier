#include "tst_validationwidget.h"

tst_validationWidget::tst_validationWidget()
{

}

void tst_validationWidget::initTestCase()
{
    validationWidget = new ValidationWidget;
    totallySpies = new QSignalSpy(validationWidget, SIGNAL(newPhoto()));
}

