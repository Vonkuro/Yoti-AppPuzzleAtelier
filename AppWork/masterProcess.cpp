#include "masterProcess.h"

MasterProcess::MasterProcess(QObject *parent) : QObject(parent)
{
    dataWrapper.setDatabase();
    puzzleHandler = new PuzzleHandler;
    link();


    test();
}

MasterProcess::~MasterProcess()
{
    delete puzzleHandler;
    dataWrapper.removeDatabase();
}

void MasterProcess::test()
{

    puzzleHandler->getNotHandled();

}

void MasterProcess::link()
{
    //connect( , puzzleHandler, &PuzzleHandler::getNotHandled);
    connect(puzzleHandler, &PuzzleHandler::puzzlesFound, puzzleHandler, &PuzzleHandler::solvePuzzle);
    connect(puzzleHandler, &PuzzleHandler::puzzleSolved, puzzleHandler, &PuzzleHandler::solvePuzzle);
    //connect(puzzleHandler, &PuzzleHandler::allPuzzleSolved, );
}
