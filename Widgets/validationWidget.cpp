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
void ValidationWidget::validateImageWebcam(int idPuzzle, int idImage, photoDevice device)
{
    viewStyle();

    puzzleId = idPuzzle;
    imageId = idImage;

    QString home = QDir::homePath();

    imagePath = home + "/Yoti-AppPuzzle/Images/Puzzle-" + QString::number(puzzleId);
    imagePath = imagePath + "/image-" + QString::number(imageId) + ".jpg";

    QString imageSize;
    if (device == Scanner)
    {
        // generate image for scanner
        double angle = 90;
        image = QPixmap::fromImage(QImage(imagePath).transformed(QMatrix().rotate(angle)));
        imageSize = "border: 2px solid #6569C4; max-width: 914px; min-width: 914px; max-height: 663px; min-height: 663px;";
    }
    else if (device == Webcam)
    {
        // generate image for webcam
        image.load(imagePath);
        imageSize = "border: 2px solid #6569C4; max-width: 914px; min-width: 914px; max-height: 690px; min-height: 690px;";
    }


    imageLabel->setPixmap(image);
    imageLabel->setStyleSheet(imageSize);
}

// Ask if an other photo is needed and emit the signal if the user confirm it
void ValidationWidget::valid()
{

    validButton->setStyleSheet(greenButtonFontStyle +
                               " " + greenCheckedButtonBackgroundStyle +
                               "height: 50px;");

    QMessageBox continueMessageBox;
    continueMessageBox.setText("Allez-vous prendre une photographe supplémentaire ?");
    continueMessageBox.addButton(tr("Oui"), QMessageBox::YesRole);
    continueMessageBox.addButton(tr("Non"), QMessageBox::NoRole);

    // Find the button in messageBox and mark them with an objectname in order to style them
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
    cancelButton->setStyleSheet(greenCheckedButtonBackgroundStyle +
                                "background-color: #E54D96; border: 2px solid #6569C4; "
                                "height: 50px;");

    QFile imageFile(imagePath);
    imageFile.remove();
    emit newPhoto();
}

// Manage details of the view
void ValidationWidget::viewStyle()
{

    QPixmap logo(":/viewRessource/logoYoti");
    logoLabel->setProperty("cssClass","logo");
    logoLabel->setScaledContents(true);
    logoLabel->setPixmap(logo);
    logoLayout->setAlignment(logoLabel,Qt::AlignHCenter);


    imageLabel->setScaledContents(true);

    titleLabel->setProperty("cssClass","title");
    titleLabel->setText("L'Image est-elle\nValide ?");
    titleLabel->setStyleSheet("text-align: center");
    widgetLayout->setAlignment(titleLabel,Qt::AlignHCenter);

    validButton->setText("Valider");
    validButton->setStyleSheet(greenButtonFontStyle +
                               " " + greenButtonBackgroundStyle +
                               "height: 50px;");
    widgetLayout->setAlignment(validButton,Qt::AlignHCenter);


    cancelButton->setText("Refuser");
    cancelButton->setStyleSheet(greenButtonFontStyle +
                                            "background-color: #E54D96; border: 2px solid #6569C4; "
                                            "height: 50px;");
    widgetLayout->setAlignment(cancelButton,Qt::AlignHCenter);

    choiceLayout->setAlignment(Qt::AlignCenter);
    choiceLayout->setSpacing(50);

    logoLayout->setAlignment(Qt::AlignTop);
    logoLayout->setSpacing(50);

    delay(100);
}
