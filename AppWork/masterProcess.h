#ifndef MASTERPROCESS_H
#define MASTERPROCESS_H

#include <QObject>
#include "puzzleHandler.h"
#include "envLocal.h"

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
    EnvLocal dataWrapper;

    void test();
    void link();
};

#endif // MASTERPROCESS_H
