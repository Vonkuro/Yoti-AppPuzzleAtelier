#include "masterProcess.h"

MasterProcess::MasterProcess(QObject *parent) : QObject(parent)
{
    dataWrapper.setDatabase();
    puzzleHandler = new PuzzleHandler;
    //test();
}

MasterProcess::~MasterProcess()
{
    delete puzzleHandler;
    dataWrapper.removeDatabase();
}

void MasterProcess::test()
{

    puzzleHandler->getNotHandled();

    puzzleHandler->solvePuzzle();

    puzzleHandler->solvePuzzle();
}
