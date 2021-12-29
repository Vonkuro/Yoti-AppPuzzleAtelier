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
    delete barcodeErrorLabel;
    delete descriptionLabel;
    delete descriptionTextEdit;
    delete descriptionErrorLabel;
    delete validationButton;
}

void SavePuzzleWidget::form()
{
// init of View Objects
    formLayout = new QFormLayout;
    barcodeLabel = new QLabel;
    barcodeLineEdit = new QLineEdit;
    barcodeErrorLabel = new QLabel;
    descriptionLabel = new QLabel;
    descriptionTextEdit = new QTextEdit;
    descriptionErrorLabel = new QLabel;

// linking View Objects
    formLayout->addRow(barcodeLabel, barcodeLineEdit);
    formLayout->addRow(descriptionLabel, descriptionTextEdit);

// style of View Objects
    barcodeLabel->setText("Code Barre : ");
    barcodeErrorLabel->setText("Un code bare doit contenir uniquement des chiffres.");
    descriptionLabel->setText("Une description rapide du Puzzle (optionnel) :");
    descriptionErrorLabel->setText("La description est trop longue.");
}

bool SavePuzzleWidget::barcodeValid(QString barcodeText) // a tester
{
    QMessageBox choiceBarcodeMessageBox;
    choiceBarcodeMessageBox.addButton(tr("Oui"), QMessageBox::YesRole);
    choiceBarcodeMessageBox.addButton(tr("Non"), QMessageBox::NoRole);

    QRegExp notNumeric;
    notNumeric.setPattern("[^0-9 .]+");
    if ( barcodeText.contains(notNumeric))
    {

        formLayout->insertRow(1,barcodeErrorLabel);
        return false;
    }

    if (barcodeText.size() == 0)
    {
        choiceBarcodeMessageBox.setText("Vous n'avez pas indiqué de code barre.");
        choiceBarcodeMessageBox.setInformativeText("Le Puzzle en est-il dépourvu ?");

        int returnMessageBox = choiceBarcodeMessageBox.exec();

        if (returnMessageBox == 0)
        {
            barcodeLineEdit->setText("0000000000000");
            return true;
        } else
        {
            return false;
        }
    }
    else if (barcodeText.size() != 13)
    {

        choiceBarcodeMessageBox.setText("Le code barre indiqué ne respecte pas le standard actuel à 13 chiffres.");
        choiceBarcodeMessageBox.setInformativeText("S'agit-il d'un code barre avec un format ancien ou rare ?");

        int returnMessageBox = choiceBarcodeMessageBox.exec();

        if (returnMessageBox == 0)
        {
            return true;
        } else
        {
            return false;
        }
    } else
    {
        return true;
    }

}

bool SavePuzzleWidget::descriptionValid(QString description) // a tester
{
    if (description.size() > 256)
    {
        formLayout->insertRow(50,descriptionErrorLabel);
        return false;
    }
    return true;
}


void SavePuzzleWidget::save()
{
    QString barcodeText = barcodeLineEdit->text();
    QRegExp whitespaceRegExp;
    whitespaceRegExp.setPattern("\\s");
    barcodeText = barcodeText.remove(whitespaceRegExp);

    if ( barcodeValid( barcodeText ) && descriptionValid( descriptionTextEdit->toPlainText() ) )
    {
        // appel fonction pour gestion des codes barres
        barcodeText = barcodeLineEdit->text();
        barcodeText = barcodeText.remove(whitespaceRegExp);

        long long int barcode = barcodeText.toLongLong();

        if ( ! dataWrapper.database.open() )
        {
            // gestion de problème à étendre
            QMessageBox::information(this, "Erreur", "La base de données n'est pas correctement installée.");
            QCoreApplication::quit();
        }
        QSqlQuery newPuzzleSql;
        if (descriptionTextEdit->toPlainText().size() == 0)
        {
            newPuzzleSql.prepare("INSERT INTO Puzzle (barcode) VALUES (?);");
            newPuzzleSql.bindValue(0, barcode);
        } else
        {
            newPuzzleSql.prepare("INSERT INTO Puzzle (barcode, short_description) VALUES (?, ?);");
            newPuzzleSql.bindValue(0, barcode);
            newPuzzleSql.bindValue(1, descriptionTextEdit->toPlainText() );
        }
        newPuzzleSql.exec();

        newPuzzleSql.prepare("SELECT id FROM Puzzle ORDER BY id DESC LIMIT 1;");
        newPuzzleSql.exec();
        newPuzzleSql.next();
        int id = newPuzzleSql.value("id").toInt();

        dataWrapper.database.close();

        emit puzzleSaved(id);
    }
}


