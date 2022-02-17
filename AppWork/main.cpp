#include <QCoreApplication>
#include "masterProcess.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MasterProcess* master = new MasterProcess(&a);

    return a.exec();
}
