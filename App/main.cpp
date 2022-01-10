#include "masterWidget.h"
#include <QApplication>
#include "choiceScannerWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MasterWidget w;
    //w.show();
    ChoiceScannerWidget c;
    c.searchScanner(5);
    c.show();
    return a.exec();
}
