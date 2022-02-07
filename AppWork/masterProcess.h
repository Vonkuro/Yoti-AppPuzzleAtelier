#ifndef MASTERPROCESS_H
#define MASTERPROCESS_H

#include <QObject>
#include "puzzleHandler.h"
#include "envLocal.h"
#include "solver.h"

class MasterProcess : public QObject
{
    Q_OBJECT
public:
    explicit MasterProcess(QObject *parent = nullptr);
    ~MasterProcess();

signals:

public slots:

private:
    PuzzleHandler* puzzleHandler;
    Solver* solver;
    EnvLocal dataWrapper;
};

#endif // MASTERPROCESS_H
