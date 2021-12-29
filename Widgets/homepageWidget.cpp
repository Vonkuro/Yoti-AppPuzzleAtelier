#include "homepageWidget.h"

HomepageWidget::HomepageWidget(QWidget *parent) : QWidget(parent)
{
    widgetLayout = new QVBoxLayout;
    startButton = new QPushButton;

    widgetLayout->addWidget(startButton);

    this->setLayout(widgetLayout);

    connect(startButton, &QPushButton::clicked, this, &HomepageWidget::startButtonClicked);

    startButton->setText("Commencer App Puzzle");
}

HomepageWidget::~HomepageWidget()
{
    delete widgetLayout;
    delete startButton;
}

void HomepageWidget::startButtonClicked()
{
    emit startApp();
}
