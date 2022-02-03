#ifndef SOLVER_H
#define SOLVER_H

#include <QObject>

class Solver : public QObject
{
    Q_OBJECT
public:
    explicit Solver(QObject *parent = nullptr);

signals:
    void puzzleSolved(int puzzleId);

public slots:
    void solvePuzzle(QMap<int, QString> puzzle);

private:
    QString commandHead;
    std::string execute(const std::string& command);
};

#endif // SOLVER_H
