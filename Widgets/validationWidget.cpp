#include "validationWidget.h"

ValidationWidget::ValidationWidget(QWidget *parent) : QWidget(parent)
{
    // Init of the View objects
    widgetLayout = new QHBoxLayout;
    choiceLayout = new QVBoxLayout;

    imageLabel = new QLabel;
    validButton = new QPushButton;
    cancelButton = new QPushButton;

    // Linking the objects to the layout
    widgetLayout->addWidget(imageLabel);
    widgetLayout->addLayout(choiceLayout);
    choiceLayout->addWidget(validButton);
    choiceLayout->addWidget(cancelButton);

    this->setLayout(widgetLayout);

    // Connect the buttons to the slots
    connect(validButton, &QPushButton::clicked, this, &ValidationWidget::valid);
    connect(cancelButton, &QPushButton::clicked, this, &ValidationWidget::cancel);

    // Style my widget !
    validButton->setText("Valide");
    cancelButton->setText("Refuse");

}

// The end of the line for the pointers
ValidationWidget::~ValidationWidget()
{
    delete widgetLayout;
    delete choiceLayout;
    delete imageLabel;
    delete validButton;
    delete cancelButton;
}

// Load the correct image to valide into the image Label
void ValidationWidget::validateImageWebcam(int idPuzzle, int idImage)
{
    puzzleId = idPuzzle;
    imageId = idImage;
    imagePath = qApp->applicationDirPath() + "/../" + "Images/Puzzle-" + QString::number(puzzleId);
    imagePath = imagePath + "/image-" + QString::number(imageId) + ".jpg";
    image.load(imagePath);
    imageLabel->setPixmap(image);
}

// Ask if an other photo is needed and emit the signal if the user confirm it
void ValidationWidget::valid()
{
    QMessageBox continueMessageBox;
    continueMessageBox.setText("Allez-vous prendre une photographe supplémentaire ?");
    continueMessageBox.addButton(tr("Oui"), QMessageBox::YesRole);
    continueMessageBox.addButton(tr("Non"), QMessageBox::NoRole);

    int returnMessageBox = continueMessageBox.exec();

    if (returnMessageBox == 0)
    {
        emit newPhoto();
    }
}

// delete the photo and emit the signal for a new photo
void ValidationWidget::cancel()
{
    QFile imageFile(imagePath);
    imageFile.remove();
    emit newPhoto();
}
