#include "homepageWidget.h"

// Set up a home page with a button to start the application
HomepageWidget::HomepageWidget(QWidget *parent) : QWidget(parent)
{
    // Init of View Objects
    widgetLayout = new QVBoxLayout;
    startButton = new QPushButton;
    logoLabel = new QLabel;
    titleLabel = new QLabel;
    subtitleLabel = new QLabel;

    // Linking the View Object
    widgetLayout->addWidget(logoLabel);
    widgetLayout->addWidget(titleLabel);
    widgetLayout->addWidget(subtitleLabel);
    widgetLayout->addWidget(startButton);
    this->setLayout(widgetLayout);

    // Connect the slots and signals
    connect(startButton, &QPushButton::clicked, this, &HomepageWidget::startButtonClicked);

    // Style the View
    viewStyle();
}

// The end of the line for the pointers
HomepageWidget::~HomepageWidget()
{
    delete logoLabel;
    delete titleLabel;
    delete subtitleLabel;
    delete startButton;
    delete widgetLayout;
}

// Emit the signal to start the Application
void HomepageWidget::startButtonClicked()
{
    emit startApp();
}

void HomepageWidget::viewStyle()
{
    QPixmap logo(":/viewRessource/logoYoti");
    logoLabel->setPixmap(logo);
    logoLabel->setProperty("cssClass","logoTitle");

    titleLabel->setText("Application Puzzle");
    titleLabel->setProperty("cssClass","title");

    subtitleLabel->setText("Prenez les pièces d'un Puzzle en images et découvrez s'il est complet !");
    subtitleLabel->setProperty("cssClass","subtitle");

    startButton->setText("Commencer");
    startButton->setProperty("cssClass","greenButton");
}
