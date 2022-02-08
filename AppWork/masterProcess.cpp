#include "masterProcess.h"

MasterProcess::MasterProcess(QObject *parent) : QObject(parent)
{
    dataWrapper.setDatabase();
    puzzleHandler = new PuzzleHandler;
    checkHour = new QTimer;
    checkHour->setInterval(3540000); // 3540000 = 59 minutes
    workHourStartInterval = QTime(18,0); // 18h00
    workHourEndInterval = QTime(19,0); // 19h00

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

    if ( verifyDatabaseAvailable() )
    {
        checkHour->start();
    } else
    {
        QCoreApplication::quit();
    }

}

bool MasterProcess::verifyDatabaseAvailable()
{
    QSqlDatabase database = dataWrapper.getDatabase();

    if (database.open())
    {
        database.close();
        return true;
    }
    return false;

}

void MasterProcess::verifyTime()
{
    QTime now = QTime::currentTime();

    if (now >= workHourStartInterval && now < workHourEndInterval)
    {

        if (verifyDatabaseAvailable())
        {
            emit timeToWork();
        } else {
            QCoreApplication::quit();
        }
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
