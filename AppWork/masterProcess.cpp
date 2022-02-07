#include "masterProcess.h"

MasterProcess::MasterProcess(QObject *parent) : QObject(parent)
{
    dataWrapper.setDatabase();
    loader = new Loader;

    loader->getNotHandled();

    std::tuple<int, QString> test = loader->getPuzzle();
    qDebug() << std::get<1>(test);

    loader->puzzleHandled(14);

    loader->getPuzzle();
    qDebug() << "I survived";

}

MasterProcess::~MasterProcess()
{
    delete loader;
    dataWrapper.removeDatabase();
}
