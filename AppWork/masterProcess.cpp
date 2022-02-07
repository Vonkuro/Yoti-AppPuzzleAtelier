#include "masterProcess.h"

MasterProcess::MasterProcess(QObject *parent) : QObject(parent)
{
    dataWrapper.setDatabase();
    puzzleHandler = new PuzzleHandler;
    solver = new Solver;

    puzzleHandler->getNotHandled();

    std::tuple<int, QString> test = puzzleHandler->getPuzzle();
    qDebug() << std::get<1>(test);

    qDebug() << solver->solvePuzzle(test);

}

MasterProcess::~MasterProcess()
{
    delete puzzleHandler;
    delete solver;
    dataWrapper.removeDatabase();
}
