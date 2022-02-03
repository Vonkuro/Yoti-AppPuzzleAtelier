#ifndef ENVLOCAL_H
#define ENVLOCAL_H
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>

class EnvLocal
{
// This class is there to set up the database and not expose the realese version to the world
// If you are an open source visitor, here is my dev/debug database
public:
    EnvLocal();
// Tools to manipulate the database
    void setDatabase();
    QSqlDatabase getDatabase();
    void removeDatabase();
private:
// Attributs
    QString dataDriver;
    QString dataName;
    QString dataUser;
    QString dataPassword;
    QString dataHost;
    int dataPort;

    QString connectionName;
};

#endif // ENVLOCAL_H
