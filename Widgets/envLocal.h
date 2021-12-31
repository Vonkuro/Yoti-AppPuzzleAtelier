#ifndef ENVLOCAL_H
#define ENVLOCAL_H
#include <QtSql>
#include <QSqlDatabase>

class EnvLocal
{
// this class is there to set up the database and not expose the realese version to the world
// if you are an open source visitor, here is my dev/debug database
public:
    EnvLocal();
    QSqlDatabase database;
private:
    QString dataDriver;
    QString dataName;
    QString dataUser;
    QString dataPassword;
    QString dataHost;
    int dataPort;
};

#endif // ENVLOCAL_H
