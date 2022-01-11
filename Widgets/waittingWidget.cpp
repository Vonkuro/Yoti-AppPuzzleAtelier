#include "waittingWidget.h"

WaittingWidget::WaittingWidget(QWidget *parent) : QWidget(parent)
{
    QString commandString = "./Yoti-PuzzleSolver ../Images/Puzzle-";
}

void WaittingWidget::solverProcess(int id)
{
    idPuzzle = id;

    commandString += QString::number(idPuzzle);
    QString solverOutput = QString::fromStdString( execute(commandString.toStdString()) );
    solverOutput = solverOutput.simplified();
    QStringList solverSplited = solverOutput.split(":");

    int piecesNumber = findPiecesNumber(solverSplited);
    bool completed = findIfCompleted(solverSplited);

    emit puzzleSolved(piecesNumber, completed);
}

int WaittingWidget::findPiecesNumber(QStringList solverSplited)
{
    QString piecesNumberString = solverSplited[1];
    int piecesNumber = piecesNumberString.toInt();

    return piecesNumber;
}

bool WaittingWidget::findIfCompleted(QStringList solverSplited)
{
    QString completedString = solverSplited[5];
    if (completedString.contains("incomplet"))
    {
        return false;
    }
    else if (completedString.contains("complet"))
    {
        return true;
    } else
    {
        return false;
    }
}
