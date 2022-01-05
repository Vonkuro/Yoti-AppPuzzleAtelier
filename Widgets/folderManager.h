#ifndef FOLDERMANAGER_H
#define FOLDERMANAGER_H

#include <QFile>
#include <QDir>

class folderManager
{
public:
    folderManager();
    void tarOldImageFolder();
private:
    void tarAFolder(QString folderName);
    void newDir(QString dirPath);
    int findPuzzleNumber(bool first = true);
};

#endif // FOLDERMANAGER_H
