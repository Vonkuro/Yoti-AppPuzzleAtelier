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

signals:
    void timeToWork();

public slots:
    void verifyTime();
    void logCycleStart();
    void logCycleEnd();
    void logPuzzle(bool solved);

private:
    PuzzleHandler* puzzleHandler;
    EnvLocal dataWrapper;

    QTimer *checkHour;
    QTime workHourStartInterval;
    QTime workHourEndInterval;

    int numberPuzzle;
    int numberFail;

    void test();
    void link();
    bool verifyDatabaseAvailable();
    void logMessage(QString message);
};

#endif // MASTERPROCESS_H
