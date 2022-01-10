#include "envLocal.h"

EnvLocal::EnvLocal()
{
// Init of attributs
    dataDriver = "QMYSQL";
    dataName = "dataPuzzle";
    dataUser = "yoti";
    dataPassword = "§Arcane2Wonder§";
    dataHost = "localhost";
    dataPort = 3306;



}

QSqlDatabase EnvLocal::getDatabase()
{
// Init of database
    QSqlDatabase database = QSqlDatabase::addDatabase(dataDriver);
    database.setDatabaseName(dataName);
    database.setUserName(dataUser);
    database.setPassword(dataPassword);
    database.setHostName(dataHost);
    database.setPort(dataPort);

    return database;
}
