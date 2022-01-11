#ifndef WAITTINGWIDGET_H
#define WAITTINGWIDGET_H

#include "common.h"

#include <QWidget>

class WaittingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WaittingWidget(QWidget *parent = nullptr);
    ~WaittingWidget();

signals:
    void puzzleSolved(int numberPieces, bool completed);
public slots:
    void solverProcess(int id);

private:
    int findPiecesNumber(QStringList solverSplited);
    bool findIfCompleted(QStringList solverSplited);


    int idPuzzle;
    QString commandString;
};

#endif // WAITTINGWIDGET_H
