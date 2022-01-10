#include "homepageWidget.h"

// Set up a home page with a button to start the application
HomepageWidget::HomepageWidget(QWidget *parent) : QWidget(parent)
{
    // Init of View Objects
    widgetLayout = new QVBoxLayout;
    startButton = new QPushButton;

    // Linking the View Object
    widgetLayout->addWidget(startButton);
    this->setLayout(widgetLayout);

    // Connect the slots and signals
    connect(startButton, &QPushButton::clicked, this, &HomepageWidget::startButtonClicked);

    // Style the View
    startButton->setText("Commencer App Puzzle");
}

// The end of the line for the pointers
HomepageWidget::~HomepageWidget()
{
    delete startButton;
    delete widgetLayout;
}

// Emit the signal to start the Application
void HomepageWidget::startButtonClicked()
{
    emit startApp();
}
