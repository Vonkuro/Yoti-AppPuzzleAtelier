#include "loader.h"

Loader::Loader(QObject *parent) : QObject(parent)
{
}

// trouver les id des puzzles non handled
// preparer le path vers le dossier image
// preparer le path vers la cover

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

        while(idNothandle.next())
        {
            int id = idNothandle.value("id").toInt();
            puzzles[id] = "../Images/Puzzle-" + QString::number(id) + "/";
            QString retour = puzzles[id];
        }

        database.close();
    }

}
