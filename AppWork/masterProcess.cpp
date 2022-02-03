#include "masterProcess.h"

MasterProcess::MasterProcess(QObject *parent) : QObject(parent)
{
    dataWrapper.setDatabase();
    loader = new Loader;

}

MasterProcess::~MasterProcess()
{
    delete loader;
    dataWrapper.removeDatabase();
}
