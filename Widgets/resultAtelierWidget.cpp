#include "resultAtelierWidget.h"

resultAtelierWidget::resultAtelierWidget(QWidget *parent) : QWidget(parent)
{
    widgetLayout = new QVBoxLayout;
    scrollLayout = new QVBoxLayout;

    scrollContainer = new QWidget;

    logoLabel = new QLabel;
    scrollArea = new QScrollArea;

    resultList = QList<OneResultWidget*>();

    this->setLayout(widgetLayout);
    widgetLayout->addWidget(logoLabel);
    widgetLayout->addWidget(scrollArea);

    scrollArea->setWidget(scrollContainer);
    scrollContainer->setLayout(scrollLayout);

    dataWrapper.setDatabase();

    showResults();
}

resultAtelierWidget::~resultAtelierWidget()
{
    delete logoLabel;
    delete scrollLayout;
    delete scrollContainer;
    delete scrollArea;
    delete widgetLayout;
}

void resultAtelierWidget::showResults()
{
    QSqlDatabase database = dataWrapper.getDatabase();
    qDebug() << "i started looking";
    if (database.open())
    {

        qDebug() << "the database open";
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

            qDebug() << "i saw a puzzle";
            int barcode = unshownPuzzle.value("barcode").toInt();
            int idPuzzle = unshownPuzzle.value("id").toInt();

            QString description = unshownPuzzle.value("short_description").toString();
            if (unshownPuzzle.isNull("completed"))
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
            qDebug() << "I have a widget to show";
            scrollLayout->addWidget(resultIterator.next());
        }

        database.close();
    }
}

