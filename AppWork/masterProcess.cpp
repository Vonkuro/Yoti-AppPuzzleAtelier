#include "masterProcess.h"

MasterProcess::MasterProcess(QObject *parent) : QObject(parent)
{
    dataWrapper.setDatabase();
    loader = new Loader;
    solver = new Solver;

    loader->getNotHandled();

    std::tuple<int, QString> test = loader->getPuzzle();
    qDebug() << std::get<1>(test);

    qDebug() << solver->solvePuzzle(test);

}

MasterProcess::~MasterProcess()
{
    delete loader;
    delete solver;
    dataWrapper.removeDatabase();
}
