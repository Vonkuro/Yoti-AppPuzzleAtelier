#include "resultAtelierWidget.h"

resultAtelierWidget::resultAtelierWidget(QWidget *parent) : QWidget(parent)
{
    widgetLayout = new QVBoxLayout;
    scrollLayout = new QVBoxLayout;


    logoLabel = new QLabel;
    scrollArea = new QScrollArea;
    finishButton = new QPushButton;

    resultList = QList<OneResultWidget*>();

    this->setLayout(widgetLayout);
    widgetLayout->addWidget(logoLabel);
    widgetLayout->addWidget(scrollArea);
    widgetLayout->addWidget(finishButton);

    scrollArea->setLayout(scrollLayout);

    dataWrapper.setDatabase();

    showResults();

    connect(finishButton, &QPushButton::clicked, this, &resultAtelierWidget::finished);
}

resultAtelierWidget::~resultAtelierWidget()
{
    deleteResults();
    delete finishButton;
    delete logoLabel;
    delete scrollLayout;
    delete scrollArea;
    delete widgetLayout;
}

void resultAtelierWidget::showResults()
{
    QSqlDatabase database = dataWrapper.getDatabase();
    if (database.open())
    {
        QSqlQuery unshownPuzzle(database);

        unshownPuzzle.prepare("SELECT * FROM Puzzle WHERE shown = FALSE;");

        unshownPuzzle.exec();

        if ( unshownPuzzle.size() == -1)
        {
            emit noResult();
            return;
        }

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

void resultAtelierWidget::deleteResults()
{
    QListIterator<OneResultWidget*> resultIterator(resultList);

    while (resultIterator.hasNext())
    {
        delete resultIterator.next();
    }
    resultList = QList<OneResultWidget*>();
}

void resultAtelierWidget::finished()
{
    emit resultHandled();
}

void resultAtelierWidget::removeResult(int idPuzzle)
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

void resultAtelierWidget::markShown(int idPuzzle)
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
