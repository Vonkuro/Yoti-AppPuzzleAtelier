#include "puzzleHandler.h"

PuzzleHandler::PuzzleHandler(QObject *parent) : QObject(parent)
{
    puzzles = QMap<int, QString>();
}


void PuzzleHandler::getNotHandled()
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
            QString home = QDir::homePath();

            int id = idNothandle.value("id").toInt();

            puzzles[id] = home + "/Yoti-AppPuzzle/Images/Puzzle-" + QString::number(id) + "/";
        }

        database.close();
        emit puzzlesFound();
    }


}

void PuzzleHandler::puzzleHandled(int puzzleId)
{
    puzzles.remove(puzzleId);
}

std::tuple<int, QString> PuzzleHandler::getPuzzle()
{
    if ( puzzles.isEmpty() )
    {
        return std::tuple<int, QString> {-1,""};
    }

    return std::tuple<int, QString> {puzzles.firstKey(),puzzles.first()};
}
