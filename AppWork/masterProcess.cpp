#include "masterProcess.h"

MasterProcess::MasterProcess(QObject *parent) : QObject(parent)
{
    dataWrapper.setDatabase();
    loader = new Loader;

    loader->getNotHandled();

    qDebug() << loader->getPuzzle();

    loader->puzzleHandled(14);

    loader->getPuzzle();
    qDebug() << "I survived";

}

MasterProcess::~MasterProcess()
{
    delete loader;
    dataWrapper.removeDatabase();
}
