#include "masterWidget.h"
#include "oneResultWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MasterWidget w;
    w.show();

    //OneResultWidget r(24, 15324895, 14, false);
    //r.show();

    return a.exec();
}
