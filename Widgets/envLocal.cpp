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

    connectionName = "Puzzle";

}

void EnvLocal::removeDatabase()
{
    QSqlDatabase::removeDatabase(connectionName);
}

QSqlDatabase EnvLocal::getDatabase()
{
    QSqlDatabase database = QSqlDatabase::database(connectionName);

    return database;
}

void EnvLocal::setDatabase()
{
// Init of database
    QSqlDatabase database = QSqlDatabase::addDatabase(dataDriver, connectionName);
    database.setDatabaseName(dataName);
    database.setUserName(dataUser);
    database.setPassword(dataPassword);
    database.setHostName(dataHost);
    database.setPort(dataPort);
}
