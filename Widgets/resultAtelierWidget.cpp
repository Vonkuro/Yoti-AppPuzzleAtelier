#include "resultAtelierWidget.h"

ResultAtelierWidget::ResultAtelierWidget(QWidget *parent) : QWidget(parent)
{
    // Init of view objects
    widgetLayout = new QVBoxLayout;
    scrollLayout = new QVBoxLayout;

    containerWidget = new QWidget;

    logoLabel = new QLabel;
    titleLabel = new QLabel;
    scrollArea = new QScrollArea;
    finishButton = new QPushButton;

    // Init of Attributs
    resultList = QList<OneResultWidget*>();

    // Linking of view objects
    this->setLayout(widgetLayout);
    widgetLayout->addWidget(logoLabel);
    widgetLayout->addWidget(titleLabel);
    widgetLayout->addWidget(scrollArea);
    widgetLayout->addWidget(finishButton);


    scrollArea->setWidget(containerWidget);
    scrollArea->setWidgetResizable(true);
    containerWidget->setLayout(scrollLayout);

    // Init of Results
    showResults();

    // Style
    viewStyle();

    // Connect to the application
    connect(finishButton, &QPushButton::clicked, this, &ResultAtelierWidget::finished);
}

// The end of the line for the pointers
ResultAtelierWidget::~ResultAtelierWidget()
{
    deleteResults();
    delete finishButton;
    delete titleLabel;
    delete logoLabel;
    delete scrollLayout;
    delete containerWidget;
    delete scrollArea;
    delete widgetLayout;
}

// Display the result that have yet to be checked by the user
void ResultAtelierWidget::showResults()
{
    QSqlDatabase database = dataWrapper.getDatabase();
    if (database.open())
    {
        QSqlQuery unshownPuzzle(database);

        unshownPuzzle.prepare("SELECT * FROM Puzzle WHERE shown = FALSE;");

        unshownPuzzle.exec();
        if ( unshownPuzzle.size() == 0)
        {
            thereIsResult = false;
            return;
        }
        thereIsResult = true;
        while(unshownPuzzle.next())
        {
            qlonglong barcode = unshownPuzzle.value("barcode").toLongLong();
            int idPuzzle = unshownPuzzle.value("id").toInt();

            QString description = unshownPuzzle.value("short_description").toString();
            if (unshownPuzzle.value("unsolvable").toBool())
            {
                OneResultWidget* newResult = new OneResultWidget(idPuzzle, barcode, description);
                resultList.append(newResult);
            } else
            {
                int pieces = unshownPuzzle.value("pieces_number").toInt();
                bool completed = unshownPuzzle.value("completed").toBool();

                OneResultWidget* newResult = new OneResultWidget(idPuzzle, barcode, description, pieces, completed);
                resultList.append(newResult);
            }
        }

        QListIterator<OneResultWidget*> resultIterator(resultList);

        while (resultIterator.hasNext())
        {
            OneResultWidget* result = resultIterator.next();
            scrollLayout->addWidget(result);
            connect(result, SIGNAL(checked(int)) ,this,SLOT(removeResult(int)));
        }

        database.close();
    }
}

// Delete the results widgets
void ResultAtelierWidget::deleteResults()
{
    QListIterator<OneResultWidget*> resultIterator(resultList);

    while (resultIterator.hasNext())
    {
        delete resultIterator.next();
    }
    resultList = QList<OneResultWidget*>();
}

// Signal the user has finish to check
void ResultAtelierWidget::finished()
{
    emit resultHandled();
}

// Verify the user really checked a result before removing them from the list
void ResultAtelierWidget::removeResult(int idPuzzle)
{
    QMessageBox verifyCheckedMessageBox;
    verifyCheckedMessageBox.addButton(tr("Oui"), QMessageBox::YesRole);
    verifyCheckedMessageBox.addButton(tr("Non"), QMessageBox::NoRole);

    QList<QAbstractButton *> buttons = verifyCheckedMessageBox.buttons();
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

    verifyCheckedMessageBox.setStyleSheet( "QLabel {font: \"Montserrat\"; color: #2C2E71}"
                                           "QMessageBox {background-color: white}"
                                           "#yesButton {font: bold \"Montserrat\"; font-size: 22px; color: #2C2E71; "
                                           " " +greenButtonBackgroundStyle +"}"
                                           "#noButton {font: bold \"Montserrat\"; font-size: 22px; color: #2C2E71; "
                                           "background-color: #E54D96; border: 2px solid #6569C4;}");

    verifyCheckedMessageBox.setText("Avez-vous ranger le Puzzle ?");

    int returnMessageBox = verifyCheckedMessageBox.exec();

    if (returnMessageBox == 0)
    {
        for (int i=0; i < resultList.size(); i++)
        {
            if (resultList[i]->puzzleId == idPuzzle)
            {
                delete resultList[i];
                resultList.removeAt(i);
            }
        }
        markShown(idPuzzle);
    }

}

// Mark a puzzle as already shown
void ResultAtelierWidget::markShown(int idPuzzle)
{
    QSqlDatabase database = dataWrapper.getDatabase();
    if (database.open())
    {
        QSqlQuery mark(database);

        mark.prepare("UPDATE Puzzle SET shown = TRUE WHERE id = ?;");
        mark.bindValue(0,idPuzzle);
        mark.exec();

        database.close();
    }
}

// Get the attribut  bool thereIsResult
bool ResultAtelierWidget::isThereResult()
{
    return thereIsResult;
}

// Manage details of the view
void ResultAtelierWidget::viewStyle()
{
    QPixmap logo(":/viewRessource/logoYoti");
    logoLabel->setProperty("cssClass","logo");
    logoLabel->setScaledContents(true);
    logoLabel->setPixmap(logo);
    widgetLayout->setAlignment(logoLabel,Qt::AlignHCenter);

    titleLabel->setText("Résultats de la veille");
    titleLabel->setProperty("cssClass","title");
    widgetLayout->setAlignment(titleLabel,Qt::AlignHCenter);

    finishButton->setText("Enregistrer de nouveaux puzzles");
    finishButton->setProperty("cssClass","greenButton");
    widgetLayout->setAlignment(finishButton, Qt::AlignHCenter);

    containerWidget->setObjectName("greenBackground");
    containerWidget->setStyleSheet("#greenBackground {background-color: #B0F2B6;}");

    scrollArea->setObjectName("blueBorder");
    scrollArea->setStyleSheet("#blueBorder {border: 2px solid #6569C4;}");

    widgetLayout->setAlignment(Qt::AlignTop);
    widgetLayout->setSpacing(25);

}
