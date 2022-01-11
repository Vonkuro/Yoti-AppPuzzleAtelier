#include "resultWidget.h"

ResultWidget::ResultWidget(QWidget *parent) : QWidget(parent)
{
    widgetLayout = new QVBoxLayout;
    piecesNumberLabel = new QLabel;
    completedLabel = new QLabel;

    widgetLayout->addWidget(piecesNumberLabel);
    widgetLayout->addWidget(completedLabel);

    this->setLayout(widgetLayout);
}

ResultWidget::~ResultWidget()
{
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
