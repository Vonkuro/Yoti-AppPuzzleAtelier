#ifndef MASTERPROCESS_H
#define MASTERPROCESS_H

#include <QObject>

class MasterProcess : public QObject
{
    Q_OBJECT
public:
    explicit MasterProcess(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MASTERPROCESS_H