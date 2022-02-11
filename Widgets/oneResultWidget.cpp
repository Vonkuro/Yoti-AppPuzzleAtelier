#include "oneResultWidget.h"

// Construct a result that failled
OneResultWidget::OneResultWidget( int idPuzzle, int barcode, QString description, QWidget *parent ) : QWidget(parent)
{
    init(idPuzzle, description);
    viewStyleCommon(barcode);
    viewStyleUnsolved();

}

// Construct a result that was solved
OneResultWidget::OneResultWidget( int idPuzzle, int barcode, QString description, int pieces, bool completed, QWidget *parent) : QWidget(parent)
{
    init(idPuzzle, description);
    viewStyleCommon(barcode);
    viewStyleSolved(pieces, completed);

}

// Initialize the widget
void OneResultWidget::init(int idPuzzle, QString description)
{
    // Init of view object
    widgetLayout = new QHBoxLayout;
    informationLayout = new QVBoxLayout;
    buttonsLayout = new QHBoxLayout;

    coverLabel = new QLabel;
    barcodeLabel = new QLabel;
    completedLabel = new QLabel;
    piecesLabel = new QLabel;

    shortDescriptionButton = new QPushButton;
    checkedButton = new QPushButton;

     // Linking the view objects
    this->setLayout(widgetLayout);
    widgetLayout->addWidget(coverLabel);
    widgetLayout->insertLayout(1,informationLayout);

    informationLayout->addWidget(barcodeLabel);
    informationLayout->addWidget(completedLabel);
    informationLayout->addWidget(piecesLabel);
    informationLayout->insertLayout(3,buttonsLayout);

    buttonsLayout->addWidget(shortDescriptionButton);
    buttonsLayout->addWidget(checkedButton);

    // Init of attributs
    QString home = QDir::homePath();
    pathCover = home + "/Yoti-AppPuzzle/Images/Puzzle-" + QString::number(idPuzzle) + "/Cover/box.jpg";

    shortDescription = description;
    if (description.isEmpty())
    {
        shortDescription = "Aucune description n'a été donnée.";
    }
    puzzleId = idPuzzle;
}

// The end of the line for pointer
OneResultWidget::~OneResultWidget()
{
    delete coverLabel;
    delete barcodeLabel;
    delete completedLabel;
    delete piecesLabel;
    delete shortDescriptionButton;
    delete checkedButton;
    delete buttonsLayout;
    delete informationLayout;
    delete widgetLayout;
}

// Style common of the solved and failled result
void OneResultWidget::viewStyleCommon(int barcode)
{
    QPixmap cover(pathCover);
    coverLabel->setPixmap(cover);
    coverLabel->setScaledContents(true);
    coverLabel->setStyleSheet(" max-width: 312; min-width: 312; max-height: 234px; min-height: 234px; border: 2px solid #6569C4; ");

    QString barcodeString = "Code barre : " + QString::number(barcode);
    barcodeLabel->setText(barcodeString);
    barcodeLabel->setProperty("cssClass","subtitle");
    informationLayout->setAlignment(barcodeLabel,Qt::AlignHCenter);

    shortDescriptionButton->setText("Description Rapide");
    shortDescriptionButton->setStyleSheet(greenButtonFontStyle + greenButtonBackgroundStyle);
    connect(shortDescriptionButton, &QPushButton::clicked, this, &OneResultWidget::displayDescription);

    checkedButton->setText("Ranger");
    checkedButton->setStyleSheet(greenButtonFontStyle + greenButtonBackgroundStyle);
    connect(checkedButton,&QPushButton::clicked,this,&OneResultWidget::check);

    informationLayout->setAlignment(Qt::AlignBottom);
    informationLayout->setSpacing(40);

    QSize widgetSize(1200,256);
    this->setMaximumSize(widgetSize);
    this->setMinimumSize(widgetSize);
}

// Style of the solved result
void OneResultWidget::viewStyleSolved(int pieces, bool completed)
{
    QString completedString = "Le Puzzle est ";
    if (completed)
    {
        completedString += "Complet";
    } else
    {
        completedString += "Incomplet";
    }
    completedLabel->setText(completedString);
    completedLabel->setProperty("cssClass","subtitle");
    informationLayout->setAlignment(completedLabel,Qt::AlignHCenter);

    QString piecesString = "Le Puzzle contient " + QString::number(pieces) + " Pièces";
    piecesLabel->setText(piecesString);
    piecesLabel->setProperty("cssClass","subtitle");
    informationLayout->setAlignment(piecesLabel,Qt::AlignHCenter);
}

// Style of the failled result
void OneResultWidget::viewStyleUnsolved()
{
    completedLabel->setText("Yoti App Puzzle n'est pas capable de résoudre ce Puzzle...");
    completedLabel->setProperty("cssClass","subtitle");
    informationLayout->setAlignment(completedLabel,Qt::AlignHCenter);

    piecesLabel->setText("Yoti App Puzzle est désolé...");
    piecesLabel->setProperty("cssClass","subtitle");
    informationLayout->setAlignment(piecesLabel,Qt::AlignHCenter);
}

// Signal that the resulut has been checked
void OneResultWidget::check()
{
    emit checked(puzzleId);
}

// Display the description of the puzzle in a message box
void OneResultWidget::displayDescription()
{
    QMessageBox descriptionMessageBox;
    descriptionMessageBox.setText(shortDescription);
    descriptionMessageBox.setStyleSheet("QLabel {font: \"Montserrat\"; color: #2C2E71}"
                                        "QMessageBox {background-color: white}"
                                        "QPushButton {font: bold \"Montserrat\"; font-size: 22px; color: #2C2E71; "
                                        " " +greenButtonBackgroundStyle +" min-width : 100}");
    descriptionMessageBox.exec();
}
