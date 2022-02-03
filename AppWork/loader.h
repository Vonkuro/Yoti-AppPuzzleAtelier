#ifndef LOADER_H
#define LOADER_H

#include <QObject>
#include <QMap>
#include <QVariant>
#include <QDebug>
#include "envLocal.h"

class Loader : public QObject
{
    Q_OBJECT
public:
    explicit Loader(QObject *parent = nullptr);
    void getNotHandled();

signals:
    void puzzlesFound();

public slots:

private:

    EnvLocal dataWrapper;
    QMap<int, QString> puzzles;

};

#endif // LOADER_H
