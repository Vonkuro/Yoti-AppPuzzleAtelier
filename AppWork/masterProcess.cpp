#include "masterProcess.h"

MasterProcess::MasterProcess(QObject *parent) : QObject(parent)
{
    dataWrapper.setDatabase();
    puzzleHandler = new PuzzleHandler;

    puzzleHandler->getNotHandled();

    std::tuple<int, QString> test = puzzleHandler->getPuzzle();
    qDebug() << std::get<1>(test);

    qDebug() << puzzleHandler->solvePuzzle(test);

}

MasterProcess::~MasterProcess()
{
    delete puzzleHandler;
    dataWrapper.removeDatabase();
}
