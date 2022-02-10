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




void PuzzleHandler::solvePuzzle()
{
    if (puzzles.empty())
    {
        emit allPuzzleSolved();
        return;
    }
    QString command = commandHead + puzzles.first();
    QString result = QString::fromStdString (execute(command));

    result = result.simplified();

    bool solved = false;
    if (result.contains("Nombre")){
        solved = true;
        QStringList resultSplited = result.split(":");

        int piecesNumber = findPiecesNumber(resultSplited);
        bool completed = findIfCompleted(resultSplited);
        saveWithResult(piecesNumber, completed);
    } else
    {
        saveWithoutResult();
    }

    emit puzzleSolved(solved);

}

// Extract the number of pieces from the splited output
int PuzzleHandler::findPiecesNumber(QStringList solverSplited)
{
    QString piecesNumberString = solverSplited[1];

    int indexEnd = piecesNumberString.indexOf("Nombre");
    indexEnd -= 2;

    piecesNumberString = piecesNumberString.mid(1,indexEnd);

    int piecesNumber = piecesNumberString.toInt();

    return piecesNumber;
}

// Extract the information of if the puzzle is complet or not
bool PuzzleHandler::findIfCompleted(QStringList solverSplited)
{
    QString completedString = solverSplited[2];
    if (completedString.contains("incomplet"))
    {
        return false;
    }
    else if (completedString.contains("complet"))
    {
        return true;
    } else
    {
        return false;
    }
}

void PuzzleHandler::saveWithResult(int piecesNumber, bool completed)
{
    QSqlDatabase database = dataWrapper.getDatabase();

    if (database.open())
    {
        QSqlQuery handled(database);
        handled.prepare("UPDATE Puzzle SET pieces_number = ? , completed = ? , handled = TRUE, unsolvable = FALSE , shown = FALSE WHERE id = ?;");
        handled.bindValue(0, piecesNumber);
        handled.bindValue(1, completed);
        handled.bindValue(2, puzzles.firstKey());

        handled.exec();

        puzzles.remove(puzzles.firstKey());

        database.close();
    }
}

void PuzzleHandler::saveWithoutResult()
{
    QSqlDatabase database = dataWrapper.getDatabase();

    if (database.open())
    {
        QSqlQuery notHandled(database);
        notHandled.prepare("UPDATE Puzzle SET handled = TRUE, unsolvable = TRUE, shown = FALSE WHERE id = ?;");
        notHandled.bindValue(0, puzzles.firstKey());

        notHandled.exec();

        puzzles.remove(puzzles.firstKey());

        database.close();
    }

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

bool PuzzleHandler::databaseReady()
{
    QSqlDatabase database = dataWrapper.getDatabase();

    if (database.open())
    {
        database.close();
        return true;
    }
    else
    {
        return false;
    }
}

void PuzzleHandler::tarOldImageFolder()
{
    // Map the Images directory

    QString home = QDir::homePath();
    QString directoryPath = home + "/Yoti-AppPuzzle/Images";
    QDir images(directoryPath);
    QStringList puzzleList = images.entryList();
    int lastId = findPuzzleNumber(puzzleList, false);

    // Prepare the tar archive command
    QString exclusion = checkForExclusion(lastId);

    QDateTime date = QDateTime::currentDateTime();
    QString dateString = date.toString("dd_MM_yyyy-hh_mm_ss");

    QString commandQString = "tar -Jcvf " + home + "/Yoti-AppPuzzle/Archive/Images-" + dateString +".tar.xz" + exclusion + " " + directoryPath;

    // Convert the command to const char* in order to transmit it to bash terminal
    std::string commandString = commandQString.toStdString();
    const char* command = commandString.c_str();
    system(command);

    // Delete most of the archived Puzzle directory
    markPuzzleArchived();
    deleteOldImageFolder(puzzleList);

}

QString PuzzleHandler::checkForExclusion(int lastId)
{
    QSqlDatabase database = dataWrapper.getDatabase();

    if ( database.open() )
    {
        exluded = QList<int>();
        QString exclusion = QString();
        QString exclusionPartOne = QString(" --exclude=\"Puzzle-");


        QSqlQuery newPuzzleSql(database);
        newPuzzleSql.prepare("SELECT id FROM Puzzle WHERE shown = TRUE ORDER By id DESC LIMIT 1;");
        newPuzzleSql.exec();
        newPuzzleSql.next();

        int idLastShown = newPuzzleSql.value("id").toInt();

        newPuzzleSql.prepare("SELECT id FROM Puzzle WHERE shown = FALSE AND id < ?;");
        newPuzzleSql.bindValue(0,idLastShown);

        while (newPuzzleSql.next()) {
            int idPuzzle = newPuzzleSql.value("id").toInt();
            exclusion = exclusion + exclusionPartOne + QString::number(idPuzzle) + "\"";
            exluded.append(idPuzzle);
        }

        for(int i = lastId; i > idLastShown; i--)
        {
            exluded.append(i);
            qDebug() << i;
            exclusion = exclusion + exclusionPartOne + QString::number(i) + "\"";
        }

        database.close();
        return exclusion;
    }
    return QString();
}

int PuzzleHandler::findPuzzleNumber(QStringList puzzleList, bool first) // test needed
{
    int number = 0;
    foreach (QString puzzle, puzzleList) {
        int numberSize = puzzle.size() - 7;
        int numberNew = puzzle.right(numberSize).toInt();
        if (first)
        {
            if (number > numberNew)
            {
                number = numberNew;
            }
        }
        else
        {
            if (number < numberNew)
            {
                number = numberNew;
            }
        }
    }
    return number;
}

void PuzzleHandler::markPuzzleArchived()
{
    QSqlDatabase database = dataWrapper.getDatabase();

    if ( database.open() )
    {
        QSqlQuery markQuerry(database);
        markQuerry.prepare("UPDATE Puzzle SET archived = TRUE WHERE shown = TRUE;");
        markQuerry.exec();
        database.close();
    }

}

void PuzzleHandler::deleteOldImageFolder(QStringList puzzleList)
{
    foreach (QString puzzle, puzzleList) {
        int numberSize = puzzle.size() - 7;
        int number = puzzle.right(numberSize).toInt();
        if ( exluded.indexOf(number) == -1 && puzzle != "." && puzzle != "..")
        {
            QString home = QDir::homePath();
            QString directoryPath = home + "/Yoti-AppPuzzle/Images";
            QString puzzlePath = directoryPath + "/" + puzzle + "/";
            QDir puzzleFolder(puzzlePath);

            puzzleFolder.removeRecursively();

        }
    }
}
