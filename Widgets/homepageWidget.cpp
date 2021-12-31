#include "homepageWidget.h"

// set up a home page with a button to start the application
HomepageWidget::HomepageWidget(QWidget *parent) : QWidget(parent)
{
    widgetLayout = new QVBoxLayout;
    startButton = new QPushButton;

    widgetLayout->addWidget(startButton);

    this->setLayout(widgetLayout);

    connect(startButton, &QPushButton::clicked, this, &HomepageWidget::startButtonClicked);

    startButton->setText("Commencer App Puzzle");
}

// the end of the line for the pointers
HomepageWidget::~HomepageWidget()
{
    delete widgetLayout;
    delete startButton;
}

// emit the signal to start the Application
void HomepageWidget::startButtonClicked()
{
    emit startApp();
}
