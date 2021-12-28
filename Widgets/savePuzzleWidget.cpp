#include "savePuzzleWidget.h"

SavePuzzleWidget::SavePuzzleWidget()
{
// init of View Objects
    widgetLayout = new QVBoxLayout;
    validationButton = new QPushButton;
    form();
// linking View Objects
    widgetLayout->addLayout(formLayout);
    widgetLayout->addWidget(validationButton);
    this->setLayout(widgetLayout);
// style of View Objects
    validationButton->setText("Enregistrer le Puzzle");
}

void SavePuzzleWidget::form()
{
// init of View Objects
    formLayout = new QFormLayout;
    barcodeLabel = new QLabel;
    barcodeSpinBox = new QLineEdit;
    descriptionLabel = new QLabel;
    descriptionTextEdit = new QTextEdit;

// linking View Objects
    formLayout->addRow(barcodeLabel,barcodeSpinBox);
    formLayout->addRow(descriptionLabel, descriptionTextEdit);

// style of View Objects
    barcodeLabel->setText("Code Barre : ");
    descriptionLabel->setText("Une description rapide du Puzzle (optionnel) :");
}

bool SavePuzzleWidget::barcodeValid(QString barcode) // a tester
{
    QRegExp notNumeric;
    notNumeric.setPattern("[^0-9 .]+");
    if ( barcode.size() > 13 || barcode.size() < 1 || barcode.contains(notNumeric))
    {
        return false;
    }
    return true;
}

bool SavePuzzleWidget::descriptionValid(QString description) // a tester
{
    if (description.size() > 256)
    {
        return false;
    }
    return true;
}
