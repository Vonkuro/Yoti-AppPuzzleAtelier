#include "resultWidget.h"

ResultWidget::ResultWidget(QWidget *parent) : QWidget(parent)
{
    widgetLayout = new QVBoxLayout;
    piecesNumberLabel = new QLabel;
    completedLabel = new QLabel;
    restartButton = new QPushButton;

    widgetLayout->addWidget(piecesNumberLabel);
    widgetLayout->addWidget(completedLabel);
    widgetLayout->addWidget(restartButton);

    this->setLayout(widgetLayout);

    connect(restartButton, &QPushButton::clicked, this,&ResultWidget::emitRestart);
}

ResultWidget::~ResultWidget()
{
    delete restartButton;
    delete completedLabel;
    delete piecesNumberLabel;
    delete widgetLayout;
}

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

void ResultWidget::emitRestart()
{
    emit restart();
}
