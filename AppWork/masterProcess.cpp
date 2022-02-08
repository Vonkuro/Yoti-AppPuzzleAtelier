#include "masterProcess.h"

MasterProcess::MasterProcess(QObject *parent) : QObject(parent)
{
    dataWrapper.setDatabase();
    puzzleHandler = new PuzzleHandler;

    puzzleHandler->getNotHandled();

    qDebug() << puzzleHandler->solvePuzzle();

    qDebug() << puzzleHandler->solvePuzzle();
}

MasterProcess::~MasterProcess()
{
    delete puzzleHandler;
    dataWrapper.removeDatabase();
}
