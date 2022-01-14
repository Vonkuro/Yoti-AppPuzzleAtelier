#include "choiceCameraWidget.h"

ChoiceCameraWidget::ChoiceCameraWidget(QWidget *parent) :
    QWidget(parent)
{
// Init of view objects
    widgetLayout = new QVBoxLayout;
    choiceButton = new QPushButton;
    choiceCombobox = new QComboBox;

// Linking view objects
    widgetLayout->addWidget(choiceCombobox);
    widgetLayout->addWidget(choiceButton);

    this->setLayout(widgetLayout);

// Connect the signals and the slots
    connect(choiceButton, &QPushButton::clicked, this, &ChoiceCameraWidget::cameraChosen);
}

// The end of the line for the pointers
ChoiceCameraWidget::~ChoiceCameraWidget()
{
    delete choiceButton;
    delete choiceCombobox;
    delete widgetLayout;
}

// Look for the available cameras and store them in cameraList
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

// Emit the signal cameraSetUp loaded with the selected cameraInfo and the id of the puzzle
void ChoiceCameraWidget::cameraChosen()
{
    int index = choiceCombobox->currentData().toInt();
    QCameraInfo chosenCamera = cameraList[index];
    emit cameraSetUp(Id, chosenCamera);
}
