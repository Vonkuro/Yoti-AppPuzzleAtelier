#ifndef SOLVER_H
#define SOLVER_H

#include <QObject>
#include <fstream>
#include <iostream>
#include <QMap>

class Solver : public QObject
{
    Q_OBJECT
public:
    explicit Solver(QObject *parent = nullptr);

signals:
    void puzzleSolved(int puzzleId);

public slots:
    void solvePuzzle(std::tuple<int, QString> puzzle);

private:
    QString commandHead;
    std::string execute(QString command);
};

#endif // SOLVER_H
