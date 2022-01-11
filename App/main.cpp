#include "masterWidget.h"
#include <QApplication>
#include "waittingWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MasterWidget w;
    w.show();

    WaittingWidget wa;
    wa.solverProcess(1);

    return a.exec();
}
