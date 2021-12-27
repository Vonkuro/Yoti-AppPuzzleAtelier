#include "cameraWidget.h"
#include "ui_cameraWidget.h"

CameraWidget::CameraWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraWidget)
{
    ui->setupUi(this);
}

CameraWidget::~CameraWidget()
{
    delete ui;
}


bool CameraWidget::checkWebcamAvailable()
{
    if (QCameraInfo::availableCameras().count() > 0)
        return true;
    else
        return false;
}

void CameraWidget::test()
{
    if (checkWebcamAvailable())
    {
        QString message = "oui";
        ui->messageTestLabel->setText(message);
    }

}
