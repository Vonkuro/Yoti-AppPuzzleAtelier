#include "masterProcess.h"

MasterProcess::MasterProcess(QObject *parent) : QObject(parent)
{
    // Init of work objects
    dataWrapper.setDatabase();
    puzzleHandler = new PuzzleHandler;
    checkHour = new QTimer;

    // Init of the attribut
    checkHour->setInterval(3540000); // 3540000 = 59 minutes
    workHourStartInterval = QTime(15,0); // 15h00
    workHourEndInterval = QTime(16,0); // 16h00
    archiveHourStartInterval = QTime(14,0); // 14h00
    archiveHourEndInterval = QTime(15,0); // 15h00

    // Connect the process together
    link();

    // Make sure the database is available
    test();
}

// The end of the line for the pointer
MasterProcess::~MasterProcess()
{
    checkHour->stop();
    delete checkHour;
    delete puzzleHandler;
    dataWrapper.removeDatabase();
}

// Test if the database is available and quit if not
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

// Test if the database is available
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

// Verify what the current time and signal to work or archive when needed
void MasterProcess::verifyTime()
{
    QTime now = QTime::currentTime();

    if (now >= workHourStartInterval && now < workHourEndInterval)
    {

        if (verifyDatabaseAvailable())
        {
            numberPuzzle = 0;
            numberFail = 0;
            emit timeToWork();
        } else {
            QCoreApplication::quit();
        }
    }
    else if (now >= archiveHourStartInterval && now < archiveHourEndInterval)
    {
        emit timeToArchive();
    }
    else
    {
        checkHour->start();
    }
}

// Connect the process together
void MasterProcess::link()
{
    connect(checkHour, &QTimer::timeout , this, &MasterProcess::verifyTime);
    connect(this, &MasterProcess::timeToArchive, puzzleHandler, &PuzzleHandler::tarOldImageFolder);
    connect(this, &MasterProcess::timeToWork, puzzleHandler, &PuzzleHandler::getNotHandled);
    connect(puzzleHandler, &PuzzleHandler::puzzlesFound, this, &MasterProcess::logCycleStart);
    connect(puzzleHandler, &PuzzleHandler::puzzlesFound, puzzleHandler, &PuzzleHandler::solvePuzzle);
    connect(puzzleHandler, SIGNAL(puzzleSolved(bool)), this, SLOT(logPuzzle(bool)) );
    connect(puzzleHandler, SIGNAL(puzzleSolved(bool)), puzzleHandler, SLOT(solvePuzzle()));
    connect(puzzleHandler, SIGNAL(allPuzzleSolved()) , this, SLOT(logCycleEnd()));
    connect(puzzleHandler, SIGNAL(allPuzzleSolved()) , checkHour, SLOT(start()));
}

// Log that a work cycle started
void MasterProcess::logCycleStart()
{
    QString message = "debut d'un cycle de travail";
    logMessage(message);
}

// Log that a work cycle ended
// Log the number of Puzzles that were worked on
// Log the number of fails
void MasterProcess::logCycleEnd()
{
    QString messageNumber = "il y a eu " + QString::number( numberPuzzle ) + " puzzles verifies";
    logMessage(messageNumber);
    QString messageFail = "il y a eu " + QString::number( numberFail ) + " erreurs";
    logMessage(messageFail);
    if (numberPuzzle != 0)
    {
        int percent = 100 * ( numberFail / numberPuzzle );
        QString messageFailPerCent = "cela correcpond à " + QString::number( percent ) + " % d'ereurs";
        logMessage(messageFailPerCent);
    }

    QString messageEnd = "fin d'un cycle de travail";
    logMessage(messageEnd);
}

// Count up a puzzle that was worked on for latter log
void MasterProcess::logPuzzle(bool solved)
{
    numberPuzzle += 1;
    if ( ! solved )
    {
        numberFail += 1;
    }
}

// Log a message in the file log.txt
void MasterProcess::logMessage(QString message) {

    QString home = QDir::homePath();
    QString filename = home + "/Yoti-AppPuzzle/log.txt";

    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("dd/MM/yyyy-hh:mm:ss");
    formattedTime += "  ";

    QFile file(filename);
    if (file.open(QIODevice::ReadWrite | QIODevice::Append)) {
        QTextStream stream(&file);
        stream << formattedTime << message << endl;
    }
}
