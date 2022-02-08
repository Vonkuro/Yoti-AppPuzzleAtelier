#include "oneResultWidget.h"

OneResultWidget::OneResultWidget(QWidget *parent,int idPuzzle, int barcode) : QWidget(parent)
{
    init(idPuzzle);


}
OneResultWidget::OneResultWidget(QWidget *parent = nullptr, int idPuzzle, int barcode, int pieces, bool completed)
{
    init(idPuzzle);
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

    widgetLayout->addWidget(coverLabel);
    widgetLayout->insertLayout(1,informationLayout);

    informationLayout->addWidget(barcodeLabel);
    informationLayout->addWidget(completedLabel);
    informationLayout->addWidget(piecesLabel);
    informationLayout->insertLayout(3,buttonsLayout);

    buttonsLayout->addWidget(shortDescriptionButton);
    buttonsLayout->addWidget(checkedButton);


    QString home = QDir::homePath();
    //pathCover = home + "/Yoti-AppPuzzle/Images/Puzzle-" + ;
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
