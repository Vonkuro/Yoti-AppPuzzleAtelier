#ifndef MASTERPROCESS_H
#define MASTERPROCESS_H

#include <QObject>
#include "loader.h"
#include "envLocal.h"

class MasterProcess : public QObject
{
    Q_OBJECT
public:
    explicit MasterProcess(QObject *parent = nullptr);
    ~MasterProcess();

signals:

public slots:

private:
    Loader* loader;
    EnvLocal dataWrapper;
};

#endif // MASTERPROCESS_H
