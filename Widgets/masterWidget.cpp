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
    homepageWidget = new HomepageWidget;
    savePuzzleWidget = new SavePuzzleWidget;
    cameraWidget = new CameraWidget();
    validationWidget = new ValidationWidget;

    masterStackedWidget->addWidget(homepageWidget);
    masterStackedWidget->addWidget(savePuzzleWidget);
    masterStackedWidget->addWidget(cameraWidget);
    masterStackedWidget->addWidget(validationWidget);

}

MasterWidget::~MasterWidget()
{
    delete homepageWidget;
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

void MasterWidget::goToWebcam(int id)
{
    masterStackedWidget->setCurrentWidget(cameraWidget);

    cameraWidget->prepare(id);
    cameraWidget->start();
}

void MasterWidget::goToWebcam()
{
    masterStackedWidget->setCurrentWidget(cameraWidget);

    cameraWidget->start();
}

void MasterWidget::goToSavePuzzle()
{
    masterStackedWidget->setCurrentWidget(savePuzzleWidget);
}

void MasterWidget::goToValidation(int idPuzzle, int idImage)
{
    validationWidget->validateImageWebcam(idPuzzle, idImage);
    masterStackedWidget->setCurrentWidget(validationWidget);
}

MasterWidget::pages MasterWidget::getLoadedPage()
{
    QWidget* currentWidget = masterStackedWidget->currentWidget();

    if (currentWidget == homepageWidget)
    {
        return homepage;
    }
    else if (currentWidget == savePuzzleWidget)
    {
        return savePuzzle;
    }
    else if (currentWidget == cameraWidget)
    {
        return camera;
    }
    else if (currentWidget == validationWidget)
    {
        return validation;
    }
    else
    {
        return noPage;
    }

}

void MasterWidget::test()
{

    // these testing connect will be almost good to go for the full application
    connect(homepageWidget, &HomepageWidget::startApp, this, &MasterWidget::goToSavePuzzle);
    connect(savePuzzleWidget, SIGNAL(puzzleSaved(int)) , this, SLOT(goToWebcam(int)));
    connect(cameraWidget, SIGNAL(photoTaken(int,int)), this, SLOT(goToValidation(int, int)));
    connect(validationWidget, SIGNAL(newPhoto()), this, SLOT(goToWebcam()));
}
