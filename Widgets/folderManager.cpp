#include "folderManager.h"

folderManager::folderManager()
{
    newDir("../Archive");
}

void folderManager::tarAFolder(QString folderName)
{
    QString commandQString = "tar -Jcf ../Archive/" + folderName + ".tar.xz ../Images/" + folderName;
    std::string commandString = commandQString.toStdString();
    const char* command = commandString.c_str();
    system(command);
}

int folderManager::findPuzzleNumber(bool first = true) // test needed
{
    QString directoryPath = "../Images";
    QDir images(directoryPath);
    QStringList puzzleList = images.entryList();
    int number = 0;
    foreach (QString puzzle, puzzleList) {
        int numberSize = puzzle.size() - 8;
        int numberNew = puzzle.right(numberSize);
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

void folderManager::tarOldImageFolder()
{

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
