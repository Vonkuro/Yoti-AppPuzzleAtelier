#ifndef ENVLOCAL_H
#define ENVLOCAL_H
#include <QtSql>
#include <QSqlDatabase>

class EnvLocal
{
// This class is there to set up the database and not expose the realese version to the world
// If you are an open source visitor, here is my dev/debug database
public:
    EnvLocal();
    void setDatabase();
    QSqlDatabase getDatabase();
    void removeDatabase();
private:
    QString dataDriver;
    QString dataName;
    QString dataUser;
    QString dataPassword;
    QString dataHost;
    int dataPort;

    QString connectionName;
};

#endif // ENVLOCAL_H
