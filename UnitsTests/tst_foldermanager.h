#ifndef TST_FOLDERMANAGER_H
#define TST_FOLDERMANAGER_H

#include <QtTest>
#include "folderManager.h"

class tst_folderManager : public QObject
{
    Q_OBJECT
public:
    tst_folderManager();

private slots:
    void findPuzzleNumberTest();
    void checkAlreadyArchivedTest();

private:
    folderManager folder;

};

#endif // TST_FOLDERMANAGER_H
