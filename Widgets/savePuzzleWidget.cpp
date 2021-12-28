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
// connect to slots
    connect(validationButton, &QPushButton::clicked, this, &SavePuzzleWidget::save);
}

SavePuzzleWidget::~SavePuzzleWidget()
{
    delete widgetLayout;
    delete formLayout;
    delete barcodeLabel;
    delete barcodeLineEdit;
    delete descriptionLabel;
    delete descriptionTextEdit;
    delete validationButton;
}

void SavePuzzleWidget::form()
{
// init of View Objects
    formLayout = new QFormLayout;
    barcodeLabel = new QLabel;
     barcodeLineEdit = new QLineEdit;
    descriptionLabel = new QLabel;
    descriptionTextEdit = new QTextEdit;

// linking View Objects
    formLayout->addRow(barcodeLabel, barcodeLineEdit);
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
        //informer utilisateur
        return false;
    }
    return true;
}

bool SavePuzzleWidget::descriptionValid(QString description) // a tester
{
    if (description.size() > 256)
    {
        //informer utilisateur
        return false;
    }
    return true;
}

long long int SavePuzzleWidget::manageBarcode()
{

}

void SavePuzzleWidget::save()
{
    if ( barcodeValid( barcodeLineEdit->text() ) || descriptionValid( descriptionTextEdit->toPlainText() ) )
    {
        // appel fonction pour gestion des codes barres
        QString barcode = barcodeLineEdit->text();

        if ( ! dataWrapper.database.open() )
        {
            // gestion de problème à étendre
            QMessageBox::information(this, "Erreur", "La base de données n'est pas correctement installée.");
            QCoreApplication::quit();
        }
        QSqlQuery newPuzzleSql;
        if (descriptionTextEdit->toPlainText().size() == 0)
        {
            newPuzzleSql.prepare("INSERT INTO Puzzle (bar_code) VALUES (?)");
            newPuzzleSql.bindValue(0,barcode);
        } else
        {
            newPuzzleSql.prepare("INSERT INTO Puzzle (bar_code, short_description) VALUES (?, ?)");
            newPuzzleSql.bindValue(0, barcode);
            newPuzzleSql.bindValue(1, descriptionTextEdit->toPlainText() );
        }
        newPuzzleSql.exec();


    }
}


