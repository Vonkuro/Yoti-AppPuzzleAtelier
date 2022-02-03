#include "loader.h"

Loader::Loader(QObject *parent) : QObject(parent)
{
    puzzles = QMap<int, QString>();
}


void Loader::getNotHandled()
{
    QSqlDatabase database = dataWrapper.getDatabase();

    if (database.open())
    {

        QSqlQuery idNothandle(database);

        idNothandle.prepare("select id from Puzzle where handled = FALSE ;");
        idNothandle.exec();

        if ( idNothandle.size() == -1)
        {
            return;
        }

        puzzles = QMap<int, QString>();

        while(idNothandle.next())
        {
            int id = idNothandle.value("id").toInt();
            puzzles[id] = "../Images/Puzzle-" + QString::number(id) + "/";
            QString retour = puzzles[id];
        }

        database.close();
        emit puzzlesFound();
    }


}

void Loader::puzzleHandled(int puzzleId)
{
    puzzles.remove(id);
}
