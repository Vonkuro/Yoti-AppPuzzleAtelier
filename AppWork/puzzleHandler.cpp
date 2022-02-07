#include "puzzleHandler.h"

PuzzleHandler::PuzzleHandler(QObject *parent) : QObject(parent)
{
    puzzles = QMap<int, QString>();

    commandHead = "Yoti-PuzzleSolver ";
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

QString PuzzleHandler::solvePuzzle(std::tuple<int, QString> puzzle)
{
    QString command = commandHead + std::get<1>(puzzle);
    QString result = QString::fromStdString (execute(command));
    return result;

}

std::string PuzzleHandler::execute(QString commandString) {
    std::string command = commandString.toStdString();
    system((command + " > temp.txt").c_str());

    std::ifstream ifs("temp.txt");
    std::string ret{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
    ifs.close(); // must close the inout stream so the file can be cleaned up
    if (std::remove("temp.txt") != 0) {
        perror("Error deleting temporary file");
    }
    return ret;
}
