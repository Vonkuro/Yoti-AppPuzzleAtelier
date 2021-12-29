#ifndef ENVLOCAL_H
#define ENVLOCAL_H
#include <QtSql>
#include <QSqlDatabase>

class EnvLocal
{
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
