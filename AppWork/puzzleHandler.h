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
    void getNotHandled();
    std::tuple<int, QString> getPuzzle();

signals:
    void puzzlesFound();
    void puzzleSolved(int puzzleId);

public slots:
    void puzzleHandled(int puzzleId);
    QString solvePuzzle(std::tuple<int, QString> puzzle);

private:

    EnvLocal dataWrapper;

    QMap<int, QString> puzzles;
    QString commandHead;

    std::string execute(QString command);

};

#endif // LOADER_H
