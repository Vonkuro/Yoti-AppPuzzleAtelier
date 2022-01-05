#include "masterWidget.h"
#include "folderManager.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MasterWidget w;
    w.show();
    w.test();
    folderManager fm;
    fm.tarAFolder("Puzzle-33");
    return a.exec();
}
