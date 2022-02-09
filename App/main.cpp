#include "masterWidget.h"
#include "resultAtelierWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MasterWidget w;
    //w.show();

    resultAtelierWidget r;
    r.show();

    return a.exec();
}
