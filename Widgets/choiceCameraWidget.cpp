#include "choiceCameraWidget.h"

ChoiceCameraWidget::ChoiceCameraWidget(QWidget *parent) :
    QWidget(parent)
{
    widgetLayout = new QVBoxLayout;
    choiceButton = new QPushButton;
    choiceCombobox = new QComboBox;

    widgetLayout->addWidget(choiceCombobox);
    widgetLayout->addWidget(choiceButton);

    this->setLayout(widgetLayout);

    connect(choiceButton, &QPushButton::clicked, this, &ChoiceCameraWidget::cameraChosen);
}

ChoiceCameraWidget::~ChoiceCameraWidget()
{
    delete choiceButton;
    delete choiceCombobox;
    delete widgetLayout;
}

void ChoiceCameraWidget::searchCamera(int id)
{
    Id = id;
    cameraList = QCameraInfo::availableCameras();
    for ( int i = 0 ; i < cameraList.size() ; i++ )
    {
        QVariant cameraInfoIndex(i);
        choiceCombobox->addItem(cameraList[i].description(),cameraInfoIndex);
    }
}

void ChoiceCameraWidget::cameraChosen()
{
    int index = choiceCombobox->currentData().toInt();
    QCameraInfo chosenCamera = cameraList[index];
    emit cameraSetUp(Id, chosenCamera);
}
