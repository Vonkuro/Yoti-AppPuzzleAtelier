#ifndef LOADER_H
#define LOADER_H

#include <QObject>

class Loader : public QObject
{
    Q_OBJECT
public:
    explicit Loader(QObject *parent = nullptr);

signals:

public slots:
};

#endif // LOADER_H