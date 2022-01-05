#ifndef FOLDERMANAGER_H
#define FOLDERMANAGER_H

#include <QFile>
#include <QDir>
#include <QDateTime>

#include "envLocal.h"

class folderManager
{
public:
    folderManager();
    void tarOldImageFolder();
private:
    void tarAFolder(QString folderName);
    void newDir(QString dirPath);
    int findPuzzleNumber(QStringList puzzleList, bool first);
    QString checkAlreadyArchived(int firstPuzzle,int lastPuzzle);
    void markPuzzleArchived(int lastPuzzle);

    int limitBeforeArchive;
// Database
    EnvLocal dataWrapper;
};

#endif // FOLDERMANAGER_H
