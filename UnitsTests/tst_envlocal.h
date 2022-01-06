#ifndef TST_ENVLOCAL_H
#define TST_ENVLOCAL_H

#include <QtTest>
#include "envLocal.h"

class tst_envLocal : public QObject
{
    Q_OBJECT

public:
    tst_envLocal();


private slots:
    void openDatabaseTest();

private:
    EnvLocal dataWrapper;

};

#endif // TST_ENVLOCAL_H
