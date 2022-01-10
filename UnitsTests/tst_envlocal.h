#ifndef TST_ENVLOCAL_H
#define TST_ENVLOCAL_H

#include <QtTest>
#include "envLocal.h"

class tst_envLocal : public QObject
{
    Q_OBJECT

public:
    tst_envLocal();

// Declaration of the Tests
private slots:
    // Unit-Tests of Methods
    void openDatabaseTest();


};

#endif // TST_ENVLOCAL_H
