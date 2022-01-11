#include "waittingWidget.h"

WaittingWidget::WaittingWidget(QWidget *parent) : QWidget(parent)
{
    // QString for the running command
    //commandString = "./Yoti-PuzzleSolver ../Images/Puzzle-";

    // Qstring for testing without photos
    commandString = "./Yoti-PuzzleSolver ../../PuzzleSolverProject/Scans/puzzle";
}

WaittingWidget::~WaittingWidget()
{

}

void WaittingWidget::solverProcess(int id)
{
    idPuzzle = id;

    commandString += QString::number(idPuzzle) + "/";
    qDebug() << commandString;
    QString solverOutput = QString::fromStdString( execute(commandString.toStdString()) );
    solverOutput = solverOutput.simplified();
    QStringList solverSplited = solverOutput.split(":");

    int piecesNumber = findPiecesNumber(solverSplited);
    bool completed = findIfCompleted(solverSplited);
    qDebug() << piecesNumber;
    qDebug() << completed;
    emit puzzleSolved(piecesNumber, completed);
}

int WaittingWidget::findPiecesNumber(QStringList solverSplited)
{
    QString piecesNumberString = solverSplited[1];

    int indexEnd = piecesNumberString.indexOf("Nombre");
    indexEnd -= 2;

    piecesNumberString = piecesNumberString.mid(1,indexEnd);

    int piecesNumber = piecesNumberString.toInt();

    return piecesNumber;
}

bool WaittingWidget::findIfCompleted(QStringList solverSplited)
{
    QString completedString = solverSplited[3];

    qDebug() << completedString;

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
