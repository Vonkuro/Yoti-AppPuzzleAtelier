#include "validationWidget.h"

ValidationWidget::ValidationWidget(QWidget *parent) : QWidget(parent)
{
    // Init of the View objects
    logoLayout = new QVBoxLayout;
    widgetLayout = new QHBoxLayout;
    choiceLayout = new QVBoxLayout;

    logoLabel = new QLabel;
    titleLabel = new QLabel;
    imageLabel = new QLabel;
    validButton = new QPushButton;
    cancelButton = new QPushButton;

    // Linking the objects to the layout
    logoLayout->addWidget(logoLabel);
    logoLayout->insertLayout(1,widgetLayout);

    widgetLayout->addWidget(imageLabel);
    widgetLayout->addLayout(choiceLayout);

    choiceLayout->addWidget(titleLabel);
    choiceLayout->addWidget(validButton);
    choiceLayout->addWidget(cancelButton);

    this->setLayout(logoLayout);

    // Connect the buttons to the slots
    connect(validButton, &QPushButton::clicked, this, &ValidationWidget::valid);
    connect(cancelButton, &QPushButton::clicked, this, &ValidationWidget::cancel);

    // Style my widget !
    viewStyle();

}

// The end of the line for the pointers
ValidationWidget::~ValidationWidget()
{
    delete logoLabel;
    delete titleLabel;
    delete imageLabel;
    delete validButton;
    delete cancelButton;
    delete choiceLayout;
    delete widgetLayout;
    delete logoLayout;
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

    QList<QAbstractButton *> buttons = continueMessageBox.buttons();
    for (QAbstractButton * button : buttons)
    {
        QPushButton* buttonPush = dynamic_cast<QPushButton*>(button);

        if ( buttonPush->text() == "Oui")
        {
            buttonPush->setObjectName("yesButton");
        } else if (buttonPush->text() == "Non")
        {
            buttonPush->setObjectName("noButton");
        }
    }
    continueMessageBox.setStyleSheet( "QLabel {font: \"Montserrat\"; color: #2C2E71}"
                                           "QMessageBox {background-color: white}"
                                           "#yesButton {font: bold \"Montserrat\"; font-size: 22px; color: #2C2E71; "
                                           "background-color: #78C29B; border: 2px solid #6569C4;}"
                                           "#noButton {font: bold \"Montserrat\"; font-size: 22px; color: #2C2E71; "
                                           "background-color: #E54D96; border: 2px solid #6569C4;}");

    int returnMessageBox = continueMessageBox.exec();

    if (returnMessageBox == 0)
    {
        emit newPhoto();
    }
    else
    {
        emit allIsValidated(puzzleId);
    }
}

// Delete the photo and emit the signal for a new photo
void ValidationWidget::cancel()
{
    QFile imageFile(imagePath);
    imageFile.remove();
    emit newPhoto();
}

void ValidationWidget::viewStyle()
{

    QPixmap logo(":/viewRessource/logoYoti");
    logoLabel->setProperty("cssClass","logo");
    logoLabel->setScaledContents(true);
    logoLabel->setPixmap(logo);
    logoLayout->setAlignment(logoLabel,Qt::AlignHCenter);

    imageLabel->setStyleSheet("border: 2px solid #6569C4; max-width: 914px; min-width: 914px; max-height: 690px; min-height: 690px; ");

    titleLabel->setProperty("cssClass","title");
    titleLabel->setText("L'Image est-elle\nValide ?");
    titleLabel->setStyleSheet("text-align: center");
    widgetLayout->setAlignment(titleLabel,Qt::AlignHCenter);

    validButton->setText("Valider");
    validButton->setStyleSheet("font: bold \"Montserrat\"; font-size: 28px; color: #2C2E71; "
                               "background-color: #78C29B; border: 2px solid #6569C4; "
                               "height: 50px;");
    widgetLayout->setAlignment(validButton,Qt::AlignHCenter);


    cancelButton->setText("Refuser");
    cancelButton->setStyleSheet("font: bold \"Montserrat\"; font-size: 28px; color: #2C2E71; "
                                            "background-color: #E54D96; border: 2px solid #6569C4; "
                                            "height: 50px;");
    widgetLayout->setAlignment(cancelButton,Qt::AlignHCenter);

    choiceLayout->setAlignment(Qt::AlignCenter);
    choiceLayout->setSpacing(50);

    logoLayout->setAlignment(Qt::AlignTop);
    logoLayout->setSpacing(50);
}
