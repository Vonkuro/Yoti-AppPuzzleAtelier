#include "resultAtelierWidget.h"

resultAtelierWidget::resultAtelierWidget(QWidget *parent) : QWidget(parent)
{
    widgetLayout = new QVBoxLayout;
    scrollLayout = new QVBoxLayout;

    scrollContainer = new QWidget;

    logoLabel = new QLabel;
    scrollArea = new QScrollArea;

    resultList = QList<OneResultWidget>();
}

resultAtelierWidget::~resultAtelierWidget()
{
    delete logoLabel;
    delete scrollLayout;
    delete scrollContainer;
    delete scrollArea;
    delete widgetLayout;
}

void resultAtelierWidget::showResults()
{

}
