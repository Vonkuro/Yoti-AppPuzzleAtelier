#include "choiceCameraWidget.h"

ChoiceCameraWidget::ChoiceCameraWidget(QWidget *parent) :
    QWidget(parent)
{
// Init of view objects
    widgetLayout = new QVBoxLayout;
    choiceButton = new QPushButton;
    choiceCombobox = new QComboBox;
    logoLabel = new QLabel;
    titleLabel = new QLabel;
    subTitleLabel = new QLabel;
// Linking view objects
    widgetLayout->addWidget(logoLabel);
    widgetLayout->addWidget(titleLabel);
    widgetLayout->addWidget(subTitleLabel);
    widgetLayout->addWidget(choiceCombobox);
    widgetLayout->addWidget(choiceButton);

    this->setLayout(widgetLayout);

// Connect the signals and the slots
    connect(choiceButton, &QPushButton::clicked, this, &ChoiceCameraWidget::cameraChosen);

    viewStyle();
}

// The end of the line for the pointers
ChoiceCameraWidget::~ChoiceCameraWidget()
{
    delete logoLabel;
    delete titleLabel;
    delete subTitleLabel;
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

    choiceButton->setStyleSheet(greenButtonBackgroundStyle);
}

// Emit the signal cameraSetUp loaded with the selected cameraInfo and the id of the puzzle
void ChoiceCameraWidget::cameraChosen()
{
    choiceButton->setStyleSheet(greenCheckedButtonBackgroundStyle);
    int index = choiceCombobox->currentData().toInt();
    QCameraInfo chosenCamera = cameraList[index];
    emit cameraSetUp(Id, chosenCamera);
}

// Manage details of the view of the webcamViewfinder
void ChoiceCameraWidget::viewStyle()
{
    QPixmap logo(":/viewRessource/logoYoti");
    logoLabel->setProperty("cssClass","logo");
    logoLabel->setScaledContents(true);
    logoLabel->setPixmap(logo);
    widgetLayout->setAlignment(logoLabel,Qt::AlignHCenter);

    titleLabel->setProperty("cssClass","title");
    titleLabel->setText("Webcams Disponibles");
    widgetLayout->setAlignment(titleLabel,Qt::AlignHCenter);

    subTitleLabel->setProperty("cssClass","subtitle");
    subTitleLabel->setText("Veuillez choisir une Webcam dans la liste");
    widgetLayout->setAlignment(subTitleLabel,Qt::AlignHCenter);

    choiceCombobox->setProperty("cssClass","choice");
    widgetLayout->setAlignment(choiceCombobox,Qt::AlignHCenter);

    choiceButton->setProperty("cssClass","greenButton");
    choiceButton->setText("Choisir cette Webcam");
    widgetLayout->setAlignment(choiceButton,Qt::AlignHCenter);

    widgetLayout->setAlignment(Qt::AlignTop);
    widgetLayout->setSpacing(50);
}
