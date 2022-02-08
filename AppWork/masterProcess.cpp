#include "masterProcess.h"

MasterProcess::MasterProcess(QObject *parent) : QObject(parent)
{
    dataWrapper.setDatabase();
    puzzleHandler = new PuzzleHandler;
    checkHour = new QTimer;
    checkHour->setInterval(60000); // 3540000 = 59 minutes
    workHourStartInterval = QTime(11,40); // 18h00
    workHourEndInterval = QTime(11,45); // 19h00

    link();


    test();
}

MasterProcess::~MasterProcess()
{
    checkHour->stop();
    delete checkHour;
    delete puzzleHandler;
    dataWrapper.removeDatabase();
}

void MasterProcess::test()
{

    checkHour->start();

}



void MasterProcess::verifyTime()
{
    QTime now = QTime::currentTime();

    if (now >= workHourStartInterval && now < workHourEndInterval)
    {
        emit timeToWork();
    } else
    {
        checkHour->start();
    }
}

void MasterProcess::link()
{
    connect(checkHour, &QTimer::timeout , this, &MasterProcess::verifyTime);
    connect(this, &MasterProcess::timeToWork, puzzleHandler, &PuzzleHandler::getNotHandled);
    connect(puzzleHandler, &PuzzleHandler::puzzlesFound, puzzleHandler, &PuzzleHandler::solvePuzzle);
    connect(puzzleHandler, &PuzzleHandler::puzzleSolved, puzzleHandler, &PuzzleHandler::solvePuzzle);
    connect(puzzleHandler, SIGNAL(allPuzzleSolved()) , checkHour, SLOT(start()));
}
