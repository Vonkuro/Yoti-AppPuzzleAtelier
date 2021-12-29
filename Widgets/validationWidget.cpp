#include "validationWidget.h"

ValidationWidget::ValidationWidget(QWidget *parent) : QWidget(parent)
{
    widgetLayout = new QHBoxLayout;
    choiceLayout = new QVBoxLayout;

    imageLabel = new QLabel;
    validButton = new QPushButton;
    cancelButton = new QPushButton;

    widgetLayout->addWidget(imageLabel);
    widgetLayout->addLayout(choiceLayout);
    choiceLayout->addWidget(validButton);
    choiceLayout->addWidget(cancelButton);

    this->setLayout(widgetLayout);

    imageLabel->setText("PlaceHolder");
    validButton->setText("Valide");
    cancelButton->setText("Invalide");

}

ValidationWidget::~ValidationWidget()
{
    delete widgetLayout;
    delete choiceLayout;
    delete imageLabel;
    delete validButton;
    delete cancelButton;
}

void ValidationWidget::validateImageWebcam(int idPuzzle, int idImage)
{
    puzzleId = idPuzzle;
    imageId = idImage;
    QString imagePath = qApp->applicationDirPath() + "/../" + "Images/Puzzle-" + QString::number(puzzleId);
    imagePath = imagePath + "/image-" + QString::number(imageId) + ".jpg";
    qDebug() << image.load(imagePath);
}
