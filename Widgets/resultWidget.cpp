#include "resultWidget.h"

ResultWidget::ResultWidget(QWidget *parent) : QWidget(parent)
{
// Init of view objects
    widgetLayout = new QVBoxLayout;
    logoLabel= new QLabel;
    completedLabel = new QLabel;
    piecesNumberLabel = new QLabel;
    restartButton = new QPushButton;

// Linking the view objects
    widgetLayout->addWidget(logoLabel);
    widgetLayout->addWidget(completedLabel);
    widgetLayout->addWidget(piecesNumberLabel);
    widgetLayout->addWidget(restartButton);

    this->setLayout(widgetLayout);

// Connect the signals and the slots
    connect(restartButton, &QPushButton::clicked, this,&ResultWidget::emitRestart);

    viewStyle();
}

// The end of the line for the pointers
ResultWidget::~ResultWidget()
{
    delete logoLabel;
    delete restartButton;
    delete completedLabel;
    delete piecesNumberLabel;
    delete widgetLayout;
}

// Display the result of a solved puzzle
void ResultWidget::display(int piecesNumber, bool completed)
{
    restartButton->setStyleSheet(greenButtonBackgroundStyle);

    QString piecesNumberString = "Le Puzzle contient " + QString::number(piecesNumber) + " pièces dans ce Puzzle.";
    piecesNumberLabel->setText(piecesNumberString);

    QString completedString = "Le Puzzle est ";
    if (completed)
    {
        completedString += "Complet.";
    } else
    {
        completedString += "Imcomplet.";
    }

    completedLabel->setText(completedString);
}

// Display excuse when the puzzle remains unsolved
void ResultWidget::display()
{
    restartButton->setStyleSheet(greenButtonBackgroundStyle);

    QString completedString = "Yoti App Puzzle n'est pas capable de résoudre ce Puzzle...";
    completedLabel->setText(completedString);

    QString piecesNumberString = "Yoti App Puzzle est désolé...";
    piecesNumberLabel->setText(piecesNumberString);
}

// Emit the restart signal
void ResultWidget::emitRestart()
{
    restartButton->setStyleSheet(greenCheckedButtonBackgroundStyle);
    emit restart();
}

// Manage details of the view
void ResultWidget::viewStyle()
{
    QPixmap logo(":/viewRessource/logoYoti");
    logoLabel->setProperty("cssClass","logo");
    logoLabel->setScaledContents(true);
    logoLabel->setPixmap(logo);
    widgetLayout->setAlignment(logoLabel,Qt::AlignHCenter);

    completedLabel->setProperty("cssClass","title");
    completedLabel->setStyleSheet("text-align: center");
    widgetLayout->setAlignment(completedLabel,Qt::AlignHCenter);

    piecesNumberLabel->setProperty("cssClass","title");
    piecesNumberLabel->setStyleSheet("text-align: center");
    widgetLayout->setAlignment(piecesNumberLabel,Qt::AlignHCenter);

    restartButton->setText("Vérifier le Puzzle Suivant");
    restartButton->setProperty("cssClass","greenButton");
    widgetLayout->setAlignment(restartButton,Qt::AlignHCenter);

    widgetLayout->setAlignment(Qt::AlignTop);
    widgetLayout->setSpacing(100);
}
