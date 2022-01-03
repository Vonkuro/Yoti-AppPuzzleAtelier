#include "scannerWidget.h"


ScannerWidget::ScannerWidget()
{
}


void ScannerWidget::prepareScanner()
{
    version = 1;
    sane_init(&version,auth_callback);

    device_list = NULL;
    SANE_Status goodToGo = SANE_STATUS_GOOD;
    if (sane_get_devices(&device_list, SANE_TRUE) == goodToGo)
    {
        device = *device_list;
        scannerHandler = new SANE_Handle;
        if (sane_open(device->name, scannerHandler) == goodToGo)
        {
            qDebug("open!");
        }
        else
        {
            qDebug("probleme chief !");
        }
    }
}

void ScannerWidget::init_v2()
{
    init();
}
