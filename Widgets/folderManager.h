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
// Method to launch the archive process if necessary
    void tarOldImageFolder();
private:
// Methods
    void tarAFolder(QString folderName);
    void newDir(QString dirPath);
    int findPuzzleNumber(QStringList puzzleList, bool first);
    QString checkAlreadyArchived(int firstPuzzle,int lastPuzzle);
    void markPuzzleArchived(int lastPuzzle);
    void deleteOldImageFolder(QStringList puzzleList,int lastPuzzle);
// Attributs
    int limitBeforeArchive;
// Database
    EnvLocal dataWrapper;
};

#endif // FOLDERMANAGER_H
