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

private:
    PuzzleHandler* puzzleHandler;
    EnvLocal dataWrapper;

    QTimer *checkHour;
    QTime workHourStartInterval;
    QTime workHourEndInterval;

    void test();
    void link();
    bool verifyDatabaseAvailable();
};

#endif // MASTERPROCESS_H
