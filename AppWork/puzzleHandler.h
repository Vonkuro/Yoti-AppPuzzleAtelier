#ifndef LOADER_H
#define LOADER_H

#include <fstream>
#include <iostream>

#include <QObject>
#include <QMap>
#include <QVariant>
#include <QDir>
#include <QDebug>
#include "envLocal.h"

class PuzzleHandler : public QObject
{
    Q_OBJECT
public:
    explicit PuzzleHandler(QObject *parent = nullptr);
    bool databaseReady();

signals:
    void puzzlesFound();
    void puzzleSolved(bool solved);
    void allPuzzleSolved();

public slots:
    void getNotHandled();
    void solvePuzzle();

private:
    EnvLocal dataWrapper;

    QMap<int, QString> puzzles;
    QString commandHead;

    int findPiecesNumber(QStringList solverSplited);
    bool findIfCompleted(QStringList solverSplited);

    void saveWithResult(int piecesNumber, bool completed);
    void saveWithoutResult();

    std::string execute(QString command);

};

#endif // LOADER_H
