#include "folderManager.h"

folderManager::folderManager()
{
    newDir("../Archive");
    limitBeforeArchive = 200;
}

void folderManager::tarAFolder(QString folderName)
{
    QString commandQString = "tar -Jcf ../Archive/" + folderName + ".tar.xz ../Images/" + folderName;
    std::string commandString = commandQString.toStdString();
    const char* command = commandString.c_str();
    system(command);
}

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
    QString directoryPath = "../Images";
    QDir images(directoryPath);
    QStringList puzzleList = images.entryList();

    int lastPuzzle = findPuzzleNumber(puzzleList, false);

    if (lastPuzzle % limitBeforeArchive != 0)
    {
        return;
    }
    else
    {
        int firstPuzzle = findPuzzleNumber(puzzleList, true);
        QString exclusion = checkAlreadyArchived(firstPuzzle, lastPuzzle);

        QDateTime date = QDateTime::currentDateTime();
        QString dateString = date.toString("dd_MM_yyyy-hh_mm_ss");

        QString commandQString = "tar -Jcvf ../Archive/Images-" + dateString +".tar.xz" + exclusion + " ../Images";
        qDebug() << commandQString;
        std::string commandString = commandQString.toStdString();
        const char* command = commandString.c_str();
        system(command);

        markPuzzleArchived(lastPuzzle);
    }
}

QString folderManager::checkAlreadyArchived(int firstPuzzle,int lastPuzzle)
{

    if ( dataWrapper.database.open() )
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

        dataWrapper.database.close();
        return exclusion;
    }
    return QString();
}

void folderManager::markPuzzleArchived(int lastPuzzle)
{
    if ( dataWrapper.database.open() )
    {
        QSqlQuery newPuzzleSql;
        newPuzzleSql.prepare("UPDATE Puzzle SET archived = 1 WHERE id <= ?");
        newPuzzleSql.bindValue(0,lastPuzzle);
        newPuzzleSql.exec();

        dataWrapper.database.close();
    }
}

void folderManager::newDir(QString dirPath)
{
    QDir dir(dirPath);
    QDir dir2;
    if(!dir.exists())
    {
        dir2.mkpath(dirPath);
    }
}
