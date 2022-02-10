#include "resultAtelierWidget.h"

ResultAtelierWidget::ResultAtelierWidget(QWidget *parent) : QWidget(parent)
{
    widgetLayout = new QVBoxLayout;
    scrollLayout = new QVBoxLayout;

    containerWidget = new QWidget;

    logoLabel = new QLabel;
    titleLabel = new QLabel;
    scrollArea = new QScrollArea;
    finishButton = new QPushButton;

    resultList = QList<OneResultWidget*>();

    this->setLayout(widgetLayout);
    widgetLayout->addWidget(logoLabel);
    widgetLayout->addWidget(titleLabel);
    widgetLayout->addWidget(scrollArea);
    widgetLayout->addWidget(finishButton);


    scrollArea->setWidget(containerWidget);
    scrollArea->setWidgetResizable(true);
    containerWidget->setLayout(scrollLayout);

    showResults();

    viewStyle();

    connect(finishButton, &QPushButton::clicked, this, &ResultAtelierWidget::finished);
}

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
            int barcode = unshownPuzzle.value("barcode").toInt();
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

void ResultAtelierWidget::deleteResults()
{
    QListIterator<OneResultWidget*> resultIterator(resultList);

    while (resultIterator.hasNext())
    {
        delete resultIterator.next();
    }
    resultList = QList<OneResultWidget*>();
}

void ResultAtelierWidget::finished()
{
    emit resultHandled();
}

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
