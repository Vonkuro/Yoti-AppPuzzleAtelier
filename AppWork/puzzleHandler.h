#ifndef LOADER_H
#define LOADER_H

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

public slots:
    void puzzleHandled(int puzzleId);

private:

    EnvLocal dataWrapper;
    QMap<int, QString> puzzles;

};

#endif // LOADER_H
