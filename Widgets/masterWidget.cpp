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
    cameraWidget = new CameraWidget();
    validationWidget = new ValidationWidget;


    masterStackedWidget->addWidget(blank);
    masterStackedWidget->addWidget(savePuzzleWidget);
    masterStackedWidget->addWidget(cameraWidget);
    masterStackedWidget->addWidget(validationWidget);

}

MasterWidget::~MasterWidget()
{
    delete blank;
    delete masterLayout;
    delete masterStackedWidget;
    delete cameraWidget;
    delete validationWidget;
}


//this function is there in order to test if the unit-test setup is correct
bool MasterWidget::testDuTest()
{
    return true;
}

void MasterWidget::gotToWebcam(int id)
{
    masterStackedWidget->setCurrentWidget(cameraWidget);

    cameraWidget->prepare(id);
    cameraWidget->start();
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

void MasterWidget::gotToValidation(int idPuzzle, int idImage)
{
    validationWidget->validateImageWebcam(idPuzzle, idImage);
    masterStackedWidget->setCurrentWidget(validationWidget);
}

void MasterWidget::test()
{
    QPushButton* buttonTest = new QPushButton;
    masterLayout->addWidget(buttonTest);

    // these testing connect will be almost good to go for the full application
    connect(buttonTest, &QPushButton::clicked, this, &MasterWidget::gotToSavePuzzle);
    connect(savePuzzleWidget, SIGNAL(puzzleSaved(int)) , this, SLOT(gotToWebcam(int)));
    connect(cameraWidget, SIGNAL(photoTaken(int,int)), this, SLOT(gotToValidation(int, int)));
}
