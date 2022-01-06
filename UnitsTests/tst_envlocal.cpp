#include "tst_envlocal.h"

tst_envLocal::tst_envLocal()
{

}


void tst_envLocal::openDatabaseTest()
{
    QVERIFY(dataWrapper.database.open());
    dataWrapper.database.close();
}
