#ifndef MASTERPROCESS_H
#define MASTERPROCESS_H

#include <QCoreApplication>
#include <QObject>
#include <QTimer>
#include <QTime>
#include "puzzleHandler.h"
#include "envLocal.h"

class MasterProcess : public QObject
{
    Q_OBJECT
public:
    explicit MasterProcess(QObject *parent = nullptr);
    ~MasterProcess();

// Manage the time
signals:
    void timeToWork();
    void timeToArchive();
public slots:
    void verifyTime();
// Manage the logs
    void logCycleStart();
    void logCycleEnd();
    void logPuzzle(bool solved);

private:
// Objects that work
    PuzzleHandler* puzzleHandler;
    EnvLocal dataWrapper;

    QTimer *checkHour;
// Attributs
    QTime workHourStartInterval;
    QTime workHourEndInterval;
    QTime archiveHourStartInterval;
    QTime archiveHourEndInterval;

    int numberPuzzle;
    int numberFail;

// Methods
    void test();
    void link();
    bool verifyDatabaseAvailable();
    void logMessage(QString message);
};

#endif // MASTERPROCESS_H
