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

// Manage details of the view
void HomepageWidget::viewStyle()
{
    QPixmap logo(":/viewRessource/logoYoti");
    logoLabel->setProperty("cssClass","logoTitle");
    logoLabel->setScaledContents(true);
    logoLabel->setPixmap(logo);
    widgetLayout->setAlignment(logoLabel,Qt::AlignHCenter);

    titleLabel->setText("Application Puzzle");
    titleLabel->setProperty("cssClass","title");
    widgetLayout->setAlignment(titleLabel,Qt::AlignHCenter);

    subtitleLabel->setText("Prenez les pièces d'un Puzzle en images et découvrez s'il est complet !");
    subtitleLabel->setProperty("cssClass","subtitle");
    widgetLayout->setAlignment(subtitleLabel,Qt::AlignHCenter);

    startButton->setText("Commencer");
    startButton->setProperty("cssClass","greenButton");
    widgetLayout->setAlignment(startButton,Qt::AlignHCenter);

    widgetLayout->setAlignment(Qt::AlignTop);
    widgetLayout->setSpacing(100);
    widgetLayout->insertSpacing(0,100);

}
