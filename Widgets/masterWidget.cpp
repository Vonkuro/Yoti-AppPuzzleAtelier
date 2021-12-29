#include "masterWidget.h"

MasterWidget::MasterWidget(QWidget *parent) :
    QWidget(parent)
{
// setup minimal view
    masterLayout = new QHBoxLayout;
    masterStackedWidget = new QStackedWidget;

    masterLayout->addWidget(masterStackedWidget);
    setLayout(masterLayout);

// loading Widgets
    blank = new QWidget;
    savePuzzleWidget = new SavePuzzleWidget;


    masterStackedWidget->addWidget(blank);
    masterStackedWidget->addWidget(savePuzzleWidget);

}

MasterWidget::~MasterWidget()
{
    delete blank;
    delete masterLayout;
    delete masterStackedWidget;
    delete cameraWidget;
}


//this function is there in order to test if the unit-test setup is correct
bool MasterWidget::testDuTest()
{
    return true;
}

void MasterWidget::startWebcam(int id)
{
    cameraWidget = new CameraWidget(id);
    masterStackedWidget->addWidget(cameraWidget);
    gotToWebcam();
}

void MasterWidget::gotToWebcam()
{
    masterStackedWidget->setCurrentWidget(cameraWidget);

    cameraWidget->start();
}

void MasterWidget::gotToSavePuzzle()
{
    masterStackedWidget->setCurrentWidget(savePuzzleWidget);
}

void MasterWidget::test()
{
    QPushButton* buttonTest = new QPushButton;
    masterLayout->addWidget(buttonTest);
    connect(buttonTest, &QPushButton::clicked, this, &MasterWidget::gotToSavePuzzle);
    connect(savePuzzleWidget, SIGNAL(puzzleSaved(int)) , this, SLOT(startWebcam(int)));
}
