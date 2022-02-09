#include "oneResultWidget.h"

OneResultWidget::OneResultWidget( int idPuzzle, int barcode, QWidget *parent ) : QWidget(parent)
{
    init(idPuzzle);
    viewStyleCommon(barcode);
    viewStyleUnsolved();

}
OneResultWidget::OneResultWidget( int idPuzzle, int barcode, int pieces, bool completed, QWidget *parent) : QWidget(parent)
{
    init(idPuzzle);
    viewStyleCommon(barcode);
    viewStyleSolved(pieces, completed);

}
void OneResultWidget::init(int idPuzzle)
{
    widgetLayout = new QHBoxLayout;
    informationLayout = new QVBoxLayout;
    buttonsLayout = new QHBoxLayout;

    coverLabel = new QLabel;
    barcodeLabel = new QLabel;
    completedLabel = new QLabel;
    piecesLabel = new QLabel;

    shortDescriptionButton = new QPushButton;
    checkedButton = new QPushButton;

    this->setLayout(widgetLayout);
    widgetLayout->addWidget(coverLabel);
    widgetLayout->insertLayout(1,informationLayout);

    informationLayout->addWidget(barcodeLabel);
    informationLayout->addWidget(completedLabel);
    informationLayout->addWidget(piecesLabel);
    informationLayout->insertLayout(3,buttonsLayout);

    buttonsLayout->addWidget(shortDescriptionButton);
    buttonsLayout->addWidget(checkedButton);


    QString home = QDir::homePath();
    pathCover = home + "/Yoti-AppPuzzle/Images/Puzzle-" + QString::number(idPuzzle) + "/Cover/box.jpg";
}

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

void OneResultWidget::viewStyleCommon(int barcode)
{
    QPixmap cover(pathCover);
    coverLabel->setPixmap(cover);
    coverLabel->setScaledContents(true);
    coverLabel->setStyleSheet(" max-width: 312; max-height: 234px  ");

    QString barcodeString = "Code barre : " + QString::number(barcode);
    barcodeLabel->setText(barcodeString);
    barcodeLabel->setProperty("cssClass","subtitle");

    shortDescriptionButton->setText("Description Rapide");

    checkedButton->setText("Ranger");

}

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

    QString piecesString = "Le Puzzle contient " + QString::number(pieces) + " Pièces";
    piecesLabel->setText(piecesString);
    piecesLabel->setProperty("cssClass","subtitle");
}

void OneResultWidget::viewStyleUnsolved()
{
    completedLabel->setText("Yoti App Puzzle n'est pas capable de résoudre ce Puzzle...");
    completedLabel->setProperty("cssClass","subtitle");

    piecesLabel->setText("Yoti App Puzzle est désolé...");
    piecesLabel->setProperty("cssClass","subtitle");
}
