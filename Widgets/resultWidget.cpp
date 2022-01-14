#include "resultWidget.h"

ResultWidget::ResultWidget(QWidget *parent) : QWidget(parent)
{
// Init of view objects
    widgetLayout = new QVBoxLayout;
    piecesNumberLabel = new QLabel;
    completedLabel = new QLabel;
    restartButton = new QPushButton;

// Linking the view objects
    widgetLayout->addWidget(piecesNumberLabel);
    widgetLayout->addWidget(completedLabel);
    widgetLayout->addWidget(restartButton);

    this->setLayout(widgetLayout);

// Connect the signals and the slots
    connect(restartButton, &QPushButton::clicked, this,&ResultWidget::emitRestart);

}

// The end of the line for the pointers
ResultWidget::~ResultWidget()
{
    delete restartButton;
    delete completedLabel;
    delete piecesNumberLabel;
    delete widgetLayout;
}

// Display the result of a solved puzzle
void ResultWidget::display(int piecesNumber, bool completed)
{
    QString piecesNumberString = "Il y a " + QString::number(piecesNumber) + " pièces dans ce Puzzle.";
    piecesNumberLabel->setText(piecesNumberString);

    QString completedString = "Ce Puzzle est ";
    if (completed)
    {
        completedString += "complet.";
    } else
    {
        completedString += "imcomplet.";
    }

    completedLabel->setText(completedString);
}

// Display excuse when the puzzle remains unsolved
void ResultWidget::display()
{
    QString piecesNumberString = "Yoti App Puzzle n'est pas capable de résoudre ce Puzzle...";
    piecesNumberLabel->setText(piecesNumberString);

    QString completedString = "Yoti App Puzzle est désolé...";
    completedLabel->setText(completedString);
}

// Emit the restart signal
void ResultWidget::emitRestart()
{
    emit restart();
}
