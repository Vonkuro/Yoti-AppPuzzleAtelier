#include "masterWidget.h"
#include <QApplication>
#include "choiceScannerWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MasterWidget w;
    w.show();

    return a.exec();
}
