#ifndef LOADER_H
#define LOADER_H

#include <fstream>
#include <iostream>

#include <QObject>
#include <QMap>
#include <QVariant>
#include <QDir>
#include <QDateTime>
#include <QList>
#include <QDebug>
#include "envLocal.h"

class PuzzleHandler : public QObject
{
    Q_OBJECT
public:
    explicit PuzzleHandler(QObject *parent = nullptr);
// Manage Database
    bool databaseReady();

// Tools for the master process
signals:
    void puzzlesFound();
    void puzzleSolved(bool solved);
    void allPuzzleSolved();
public slots:
    void getNotHandled();
    void solvePuzzle();
    void tarOldImageFolder();

private:
// Database
    EnvLocal dataWrapper;
// Structures
    struct puzzleInformation
    {
        QString path;
        bool known;
        int piecesNumber;
    };
// Attributs
    QMap<int, puzzleInformation> puzzles;
    QString commandHeadTotal;
    QString commandHeadQuick;
    QList<int> exluded;

// Methods
    int findPiecesNumber(QStringList solverSplited);
    bool findIfCompleted(QStringList solverSplited);
    void saveWithResult(int piecesNumber, bool completed);
    void saveWithoutResult();
    std::string execute(QString command);
    QString checkForExclusion(int lastId);
    void markPuzzleArchived();
    void deleteOldImageFolder(QStringList puzzleList);
    int findPuzzleNumber(QStringList puzzleList, bool first);
    void solvePuzzleTotal();
    void solvePuzzleQuick();
};

#endif // LOADER_H
