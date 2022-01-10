#include "folderManager.h"

// Prepare the directory where the Archive is stored
// Prepare the limit of new puzzle directory before archiving them
folderManager::folderManager()
{
    newDir("../Archive");
    limitBeforeArchive = 200;
}



// Find the first or last number in a list of directory name with the format "Puzzle-n" with n an INT.
int folderManager::findPuzzleNumber(QStringList puzzleList, bool first = true) // test needed
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

// WARNING
// This function should not be called multiple time during the same second
void folderManager::tarOldImageFolder()
{
    // Map the Images directory
    QString directoryPath = "../Images";
    QDir images(directoryPath);
    QStringList puzzleList = images.entryList();

    int lastPuzzle = findPuzzleNumber(puzzleList, false);

    if (lastPuzzle % limitBeforeArchive != 0)
    {
        // If under the limit nothing need to be done
        return;
    }
    else
    {
        // Prepare the tar archive command
        int firstPuzzle = findPuzzleNumber(puzzleList, true);
        QString exclusion = checkAlreadyArchived(firstPuzzle);

        QDateTime date = QDateTime::currentDateTime();
        QString dateString = date.toString("dd_MM_yyyy-hh_mm_ss");

        QString commandQString = "tar -Jcvf ../Archive/Images-" + dateString +".tar.xz" + exclusion + " ../Images";

        // Convert the command to const char* in order to transmit it to bash terminal
        std::string commandString = commandQString.toStdString();
        const char* command = commandString.c_str();
        system(command);

        // Delete most of the archived Puzzle directory
        markPuzzleArchived(lastPuzzle);
        deleteOldImageFolder(puzzleList,lastPuzzle);
    }
}

// Check in database if the puzzles with an id equal or higher than fisrtPuzzle are already archived
// If they are a QString is created with the format " --exclude=\"Puzzle-id --exclude=\"Puzzle-otherId"
// That exclude instruction is repeated as many time as there are already archived Puzzle id
// That QString is returned and could be empty
QString folderManager::checkAlreadyArchived(int firstPuzzle)
{
    QSqlDatabase database = dataWrapper.getDatabase();

    if ( database.open() )
    {
        QString exclusion = QString();
        QString exclusionPartOne = QString(" --exclude=\"Puzzle-");

        bool alreadyArchived = true;
        int idPuzzle;

        QSqlQuery newPuzzleSql;
        newPuzzleSql.prepare("SELECT id, archived FROM Puzzle WHERE id >= ?;");
        newPuzzleSql.bindValue(0,firstPuzzle);
        newPuzzleSql.exec();

        do
        {
            newPuzzleSql.next();
            alreadyArchived = newPuzzleSql.value("archived").toBool();
            if (! alreadyArchived )
            {
                break;
            }
            idPuzzle = newPuzzleSql.value("id").toInt();
            exclusion = exclusion + exclusionPartOne + QString::number(idPuzzle) + "\"";
        }while(alreadyArchived);

        database.close();
        return exclusion;
    }
    return QString();
}

// In database, mark all the puzzle with an id equal of lower than lastPuzzle as archived
void folderManager::markPuzzleArchived(int lastPuzzle)
{
    QSqlDatabase database = dataWrapper.getDatabase();

    if ( database.open() )
    {
        QSqlQuery newPuzzleSql;
        newPuzzleSql.prepare("UPDATE Puzzle SET archived = 1 WHERE id <= ?");
        newPuzzleSql.bindValue(0,lastPuzzle);
        newPuzzleSql.exec();

        database.close();
    }
}

// Delete the puzzle directory with an id less than lastPuzzle minus 10
void folderManager::deleteOldImageFolder(QStringList puzzleList,int lastPuzzle)
{
    int numberLimit = lastPuzzle - 10;
    foreach (QString puzzle, puzzleList) {
        int numberSize = puzzle.size() - 7;
        int number = puzzle.right(numberSize).toInt();
        if (number < numberLimit && puzzle != "." && puzzle != "..")
        {
            QString puzzlePath = "../Images/" + puzzle + "/";
            QDir puzzleFolder(puzzlePath);

            puzzleFolder.removeRecursively();

        }
    }
}

// Check if a directory already exits, if not create it
void folderManager::newDir(QString dirPath)
{
    QDir dir(dirPath);
    QDir dir2;
    if(!dir.exists())
    {
        dir2.mkpath(dirPath);
    }
}
