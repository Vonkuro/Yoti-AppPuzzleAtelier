#include "savePuzzleWidget.h"

SavePuzzleWidget::SavePuzzleWidget()
{
// Init of View Objects
    widgetLayout = new QVBoxLayout;
    backgroundWidget = new QWidget;
    backgroundLayout = new QVBoxLayout(backgroundWidget);
    validationButton = new QPushButton;
    logoLabel = new QLabel;
    titleLabel = new QLabel;
    form();
// Linking View Objects
    backgroundLayout->addWidget(titleLabel);
    backgroundLayout->addLayout(formLayout);

    widgetLayout->addWidget(logoLabel);
    widgetLayout->addWidget(backgroundWidget);
    widgetLayout->addWidget(validationButton);
    this->setLayout(widgetLayout);
// Style of View Objects
    viewStyle();
// Connect to slots
    connect(validationButton, &QPushButton::clicked, this, &SavePuzzleWidget::save);
}

// The end of the line for the pointers
SavePuzzleWidget::~SavePuzzleWidget()
{
    delete logoLabel;
    delete barcodeLabel;
    delete barcodeLineEdit;
    delete barcodeErrorLabel;
    delete descriptionLabel;
    delete descriptionTextEdit;
    delete descriptionErrorLabel;
    delete validationButton;
    delete formLayout;
    delete titleLabel;
    delete backgroundLayout;
    delete backgroundWidget;
    delete widgetLayout;
}

// Prepare the form
void SavePuzzleWidget::form()
{
// Init of View Objects
    formLayout = new QFormLayout;
    barcodeLabel = new QLabel;
    barcodeLineEdit = new QLineEdit;
    barcodeErrorLabel = new QLabel;
    descriptionLabel = new QLabel;
    descriptionTextEdit = new QTextEdit;
    descriptionErrorLabel = new QLabel;

// Linking View Objects
    formLayout->addRow(barcodeLabel, barcodeLineEdit);
    formLayout->addRow(descriptionLabel, descriptionTextEdit);

// Style of View Objects
    barcodeLabel->setText("Le Code Barre : ");
    barcodeLabel->setProperty("cssClass", "subtitle");

    barcodeErrorLabel->setText("Un code bare doit contenir uniquement des chiffres.");

    descriptionLabel->setText("Une description rapide du Puzzle :\n (optionnelle)");
    descriptionLabel->setProperty("cssClass", "subtitle");
    descriptionLabel->setAlignment(Qt::AlignRight);

    descriptionErrorLabel->setText("La description est trop longue.");
}

// Manage the details of the View
 void SavePuzzleWidget::viewStyle()
 {
     backgroundWidget->setMinimumSize(802,320);
     backgroundWidget->setMaximumHeight(320);
     backgroundWidget->setObjectName("greenBackground");
     backgroundWidget->setStyleSheet("#greenBackground {background-color: #B0F2B6;  border: 2px solid #6569C4;"
                                     "max-width: 800px; width: 800px;}"
                                     "");

     QPixmap logo(":/viewRessource/logoYoti");
     logoLabel->setProperty("cssClass","logo");
     logoLabel->setScaledContents(true);
     logoLabel->setPixmap(logo);
     widgetLayout->setAlignment(logoLabel,Qt::AlignHCenter);

     titleLabel->setText("Enregistrement du Puzzle");
     titleLabel->setProperty("cssClass","title");
     backgroundLayout->setAlignment(titleLabel,Qt::AlignHCenter);

     validationButton->setText("Enregistrer le Puzzle");
     validationButton->setEnabled(true);
     validationButton->setProperty("cssClass","greenButton");
     validationButton->setStyleSheet("max-width: 800px; width: 500px");
     widgetLayout->setAlignment(validationButton,Qt::AlignHCenter);

     widgetLayout->setAlignment(backgroundWidget,Qt::AlignHCenter);
     widgetLayout->setAlignment(Qt::AlignTop);
     widgetLayout->setSpacing(50);
 }

// Verify if a barcode is valid
// There is four cases :
// 1/ There are 13 numbers, the barcode is valid
// 2/ There are character that aren't numbers, the barcode is not valid
// 3/ The barcode is empty, the bare is replace by "0000000000000" if the user
//    confirm the lack of barcode
// 4/ There are only numbers but not 13 of them, the barcode is valid if
//    the user confirm it is.
bool SavePuzzleWidget::barcodeValid(QString barcodeText) // need unit-tests
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

// Verify if the short description is valid
bool SavePuzzleWidget::descriptionValid(QString description) // need unit-tests
{
    if (description.size() > 256)
    {
        formLayout->insertRow(50,descriptionErrorLabel);
        return false;
    }
    return true;
}

// Save the puzzle to the database and emit a signal
// The signal is for the master widget to display the camera
void SavePuzzleWidget::save()
{
    QString barcodeText = barcodeLineEdit->text();
    QRegExp whitespaceRegExp;
    whitespaceRegExp.setPattern("\\s");
    barcodeText = barcodeText.remove(whitespaceRegExp);

    if ( barcodeValid( barcodeText ) && descriptionValid( descriptionTextEdit->toPlainText() ) )
    {
        barcodeText = barcodeLineEdit->text();
        barcodeText = barcodeText.remove(whitespaceRegExp);

        long long int barcode = barcodeText.toLongLong();

        QSqlDatabase database = dataWrapper.getDatabase();

        if ( ! database.open() )
        {
            // Could extend into a better error handling
            QMessageBox::information(this, "Erreur", "La base de données n'est pas correctement installée.");
            QCoreApplication::quit();
        }
        QSqlQuery newPuzzleSql(database);
        if (descriptionTextEdit->toPlainText().size() == 0)
        {
            newPuzzleSql.prepare("INSERT INTO Puzzle (barcode, archived, completed) VALUES (?, FALSE, FALSE);");
            newPuzzleSql.bindValue(0, barcode);
        } else
        {
            newPuzzleSql.prepare("INSERT INTO Puzzle (barcode, short_description, archived, completed) VALUES (?, ?, FALSE, FALSE);");
            newPuzzleSql.bindValue(0, barcode);
            newPuzzleSql.bindValue(1, descriptionTextEdit->toPlainText() );
        }
        newPuzzleSql.exec();

        newPuzzleSql.prepare("SELECT id FROM Puzzle ORDER BY id DESC LIMIT 1;");
        newPuzzleSql.exec();
        newPuzzleSql.next();
        int id = newPuzzleSql.value("id").toInt();

        database.close();

        emit puzzleSaved(id);
    }
}


