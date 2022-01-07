#include "tst_envlocal.h"

// Don't change anything in the constructor or QTest will crash
tst_envLocal::tst_envLocal()
{

}

// Test if the database open, aka the App can use it
void tst_envLocal::openDatabaseTest()
{
    QVERIFY(dataWrapper.database.open());
    dataWrapper.database.close();
}


// Futur tests
    //Verify the data-structure
